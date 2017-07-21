// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef DRIVETRANSFERSERVICE_H
#define DRIVETRANSFERSERVICE_H

#include <thread>
#include <fstream>
#include <sstream>
#include <queue>

#include <QThread>

#include "OCService.h"
//#include "Transfer/DriveTransfer.h"
#include "Transfer/SequentialDriveTransfer.h"
#include <Hash/xxHashAdapter.h>
#include "Task/HashCheckTask.h"

// TODO: Refactor by moving to more suitable location and possibly renaming, possible location OCCore/Service
// Note: std::string is used instead of QString, see previous note
class IDriveTransferService : public OCService
{
    Q_OBJECT


public:
    IDriveTransferService(OCEventBus* bus) : OCService(bus)
    {
    }

    virtual ~IDriveTransferService()
    {
    }

    virtual void SetSourceDrive(std::string sourceDrive) = 0;
    virtual void SetDestinationDrives(std::vector<std::string> destinationDrives) = 0;
};

class DriveTransferService : public IDriveTransferService
{
    Q_OBJECT

    std::vector<FileTransferInfo> fileList;
    std::vector<std::string> _destinationPaths;

public:
    DriveTransferService(OCEventBus* bus) : IDriveTransferService(bus)
    {
        GetEventBus()->RegisterEventHandler<StartDriveTransferEvent, DriveTransferService>(std::bind(&DriveTransferService::StartDriveTransferEventHandler, this, std::placeholders::_1));
    }

    void SetSourceDrive(std::string sourceDrive) override
    {
    }

    void SetDestinationDrives(std::vector<std::string> destinationDrives) override
    {
    }

    bool Execute()
    {
        bool finished = false;

        return finished;
    }

    void StartDriveTransferEventHandler(const OCEvent& event)
    {
        // TODO: Conversion is necessary at the moment, as arguments are not polymorphic yet
        const StartDriveTransferEvent transferEvent = dynamic_cast<const StartDriveTransferEvent&>(event);

        EnumerateFiles(QString::fromStdString(transferEvent.GetSourcePath()), &fileList);

        _destinationPaths = transferEvent.GetDestinationPaths();

        std::vector<ITask*> tasks;

        for(std::string destination : _destinationPaths)
        {
            SequentialDriveTransfer* driveTransfer = new SequentialDriveTransfer(transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths(), &fileList);

            ReplicateFolderStructure(transferEvent.GetSourcePath(), destination);

            RegisterNewTaskEvent newTaskEvent(driveTransfer);
            GetEventBus()->FireEvent<RegisterNewTaskEvent>(newTaskEvent);

            tasks.push_back(driveTransfer);
        }

        //        SequentialDriveTransfer* driveTransfer = new SequentialDriveTransfer(transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths(), &fileList);

        //        RegisterNewTaskEvent newTaskEvent(driveTransfer);
        //        GetEventBus()->FireEvent<RegisterNewTaskEvent>(newTaskEvent);

        // TODO: Move to some central place
        qRegisterMetaType<int64_t>("int64_t");

        for(ITask* task : tasks)
        {
             SequentialDriveTransfer* t = static_cast<SequentialDriveTransfer*>(task);
             t->Execute();
//            QThread* thread = new QThread(task);
//            task->moveToThread(thread);
//            connect(thread, SIGNAL(started()), task, SLOT(Execute()));
//            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

//            connect(task, SIGNAL(FileTransfered(int, int64_t)), this, SLOT(FileTransfered(int, int64_t)));
//            connect(task, SIGNAL(TransferFinished()), this, SLOT(TransferFinished()));
//            thread->start();
        }
    }

    //void TestThread(DriveTransfer& driveTransfer) const;

    void ReplicateFolderStructure(std::string rootPath, std::string targetPath) const
    {
        QDir().mkdir(QString::fromStdString(targetPath));

        QDirIterator directories(QString::fromStdString(rootPath), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while (directories.hasNext())
        {
            directories.next();

            QString relativePath = directories.filePath();
            relativePath = relativePath.mid(static_cast<int>(rootPath.length()));
            QDir().mkdir(QString::fromStdString(targetPath) + "/" + relativePath);
        }
    }

    // Used to enumerate files in source folder, usually source drive
    void EnumerateFiles(QString path, std::vector<FileTransferInfo>* fileList)
    {
        QDir dir(path);
        QDirIterator files(path, QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files, QDirIterator::Subdirectories);

        while (files.hasNext())
        {
            files.next();

            FileTransferInfo fileInfo;
            fileInfo.FileName = files.fileName().toStdString();//.toLatin1();
            QString relativeFolder = dir.relativeFilePath(files.filePath());
            int relativePathLength = relativeFolder.length() - fileInfo.FileName.length();
            relativeFolder = relativeFolder.left(relativePathLength);
            fileInfo.RelativeFolderPath = relativeFolder.toStdString(); //files.fileInfo().path().toLatin1();
            fileList->push_back(fileInfo);

            qDebug(files.fileName().toLatin1());// std::cout << fileName << std::endl;
            qDebug(files.filePath().toLatin1());
            qDebug(files.fileInfo().path().toLatin1());
            qDebug(dir.relativeFilePath(files.filePath()).toLatin1());
        }
    }

private slots:
    void FileTransfered(int index, int64_t checksum)
    {
        fileList.at(index).Checksum = checksum;
    }

    void TransferFinished()
    {
        // TODO: Pass file list to hash check task, so the are processed as bulk, IO performance improvement
        HashCheckTask* hashCheckTask = new HashCheckTask(&fileList);
        RegisterNewTaskEvent hashTaskEvent(hashCheckTask);
        GetEventBus()->FireEvent<RegisterNewTaskEvent>(hashTaskEvent);
        QThread* thread = new QThread();
        hashCheckTask->moveToThread(thread);
        connect(thread, SIGNAL(started()), hashCheckTask, SLOT(Execute()));
        connect(hashCheckTask, SIGNAL(HashChecked(int64_t)), this, SLOT(HashChecked(int64_t)));
        thread->start();
    }

    void HashChecked(int64_t checksum)
    {
        int i = 0;
    }
};

#endif //DRIVETRANSFERSERVICE_H
