// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "HashCheckTask.h"

#include <fstream>
#include <iostream>

#include "Log/Logger.h"

HashCheckTask::HashCheckTask(std::vector<FileTransferInfo>* fileList) :
    _hashGenerator(new xxHashAdapter()),
    _fileList(fileList),
    _currentFileIndex(0)
{
}

HashCheckTask::~HashCheckTask()
{
}

unsigned int HashCheckTask::GetProgressPercentage()
{
    return _progressPercentage;
}

std::string HashCheckTask::GetTaskDescription() { return "Checksum verification"; }

std::string HashCheckTask::GetSubTaskDescription() { return _fileList->at(_currentFileIndex).FileName; }

long HashCheckTask::GetFileSize(std::ifstream& fin) const
{
    fin.seekg(0, fin.end);
    long fileSize = fin.tellg();
    fin.seekg(0, fin.beg);

    return fileSize;
}

void HashCheckTask::Execute()
{
    unsigned int progress = 0;
    unsigned int progressBlock = 100.0f / _fileList->size();
    for(FileTransferInfo fileInfo : *_fileList)
    {
        _hashGenerator->Initialize();

        std::ifstream fin(fileInfo.FullTargetPath, std::ios::in | std::ifstream::binary);
        if (!fin.is_open())
        {
            return;
        }

        long fileSize = GetFileSize(fin);

        unsigned int bufferSize = 1024 * 1024; // 1MB
        std::vector<char> buffer(fileSize, 0);

        unsigned int totalChunks = fileSize / bufferSize;
        unsigned int lastChunkSize = fileSize - (totalChunks * bufferSize);

        if (lastChunkSize != 0)
        {
            ++totalChunks;
        }

        for (unsigned int index = 0; index < totalChunks; ++index)
        {
            if (index == totalChunks - 1)
            {
                bufferSize = lastChunkSize;
            }

            fin.read(buffer.data(), bufferSize);
            _hashGenerator->Update(buffer.data(), bufferSize);
        }

        uint64_t fileHash = _hashGenerator->Retrieve();
        OC_LOG_INFO("File: " + fileInfo.FileName + " Hash: " + std::to_string(fileHash));
        if(fileHash != fileInfo.Checksum)
        {
            OC_LOG_ERROR("Checksum not equal");
        }
        else
        {
            OC_LOG_INFO("Checksum OK");
        }

        progress++;
        _progressPercentage = progress * progressBlock;

        emit TaskUpdated(this);
    }
}

void HashCheckTask::ProgressChanged(unsigned int progress)
{
    _progressPercentage = progress;

    emit TaskUpdated(this);
}
