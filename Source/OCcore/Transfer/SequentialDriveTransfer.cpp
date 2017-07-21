// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "SequentialDriveTransfer.h"
#include <QDirIterator>
#include "Log/Logger.h"
#include <QStorageInfo>

#include "Hash/xxHashAdapter.h"

SequentialDriveTransfer::SequentialDriveTransfer(std::string sourcePath, std::vector<std::string> destinationPaths, std::vector<FileTransferInfo>* fileList) :
    _sourcePath(sourcePath),
    _destinationPaths(destinationPaths),
    _fileList(fileList)
{
    int i = 0;
}

unsigned int SequentialDriveTransfer::GetProgressPercentage()
{
    return _progressPercentage;
}

std::string SequentialDriveTransfer::GetTaskDescription()
{
    return "Sequential Drive Transfer";
}

std::string SequentialDriveTransfer::GetSubTaskDescription()
{
    return _subTaskDescription;
}

void SequentialDriveTransfer::TransferFile(QString sourcePath, QString relativeFilePath, QString targetPath, int64_t& checksum)
{
    QFile source(sourcePath + "/" + relativeFilePath);

    _subTaskDescription = "Copying " + relativeFilePath.toStdString();

    // TODO: Ensure trailing slash to remove need of appending it in multiple places
    if (QFile::exists(targetPath + relativeFilePath))
    {
        QFile::remove(targetPath + "/" + relativeFilePath);
    }

    QFile target(targetPath + "/" + relativeFilePath);

    OC_LOG_INFO("From: " + source.fileName().toStdString() + " To: " + target.fileName().toStdString());
    source.open(QIODevice::ReadOnly);
    target.open(QIODevice::WriteOnly);

    if (source.error() || target.error())
    {
        OC_LOG_ERROR("SequentialDriveTransfer failed.");
        return;
    }

    //int TRANSFER_BLOCK_SIZE = 1024 * 1024; // 1MB
    int TRANSFER_BLOCK_SIZE = 64 * 1024; // 64kb

    float progressBlock = source.size() / 100.0f;
    int totalRead = 0;
    int progress = 0;

    const std::unique_ptr<IHashGenerator> hashGenerator(new xxHashAdapter());
    hashGenerator->Initialize();

    // TODO: Error handling
    char* buffer = new char[TRANSFER_BLOCK_SIZE];
    while (!source.atEnd())
    {
        qint64 readSize = source.read(buffer, TRANSFER_BLOCK_SIZE);
        target.write(buffer, readSize);

        hashGenerator->Update(buffer, readSize);

        totalRead += readSize;

         //progress = totalRead / progressBlock;

        if (totalRead > progressBlock * progress)
        {
            progress += totalRead / progressBlock;

            ProgressChanged(progress);
        }
    }

    checksum = hashGenerator->Retrieve();
}

void SequentialDriveTransfer::Execute()
{
    OC_LOG_INFO("Copying started");

    // TODO: Add handling of multiple destinations
    std::string destination = _destinationPaths[0];

    int index = 0;
    for (FileTransferInfo& info : *_fileList)
    {
        QString relativeFilePath = QString::fromStdString(info.RelativeFolderPath + info.FileName);
        int64_t checksum = 0;
        TransferFile(_sourcePath.c_str(), relativeFilePath, QString::fromStdString(destination), checksum);

        emit FileTransfered(index, checksum);

        info.FullTargetPath = destination + "/" + relativeFilePath.toStdString();
        index++;
    }

    // NOTE: Workaround, as QThread::finished() wasn't emitted
    emit TransferFinished();

    OC_LOG_INFO("Copying finished");
}

void SequentialDriveTransfer::ProgressChanged(unsigned int progress)
{
    _progressPercentage = progress;

    emit TaskUpdated(this);
}
