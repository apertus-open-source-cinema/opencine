#include "HashCheckTask.h"

#include <fstream>
#include <iostream>

#include "Log/Logger.h"

HashCheckTask::HashCheckTask(std::string fileName, uint64_t checkSum) :
    _hashGenerator(new xxHashAdapter()),
    _fileName(fileName),
    _checkSum(checkSum)
{
}

HashCheckTask::~HashCheckTask()
{
}

int HashCheckTask::GetFileSize(std::ifstream& fin) const
{
	fin.seekg(0, fin.end);
	int fileSize = fin.tellg();
	fin.seekg(0, fin.beg);

	return fileSize;
}

void HashCheckTask::Execute()
{
	//std::string targetFile = "E:/Temp/OC_COPY/ARRI/C001C005_140702_R3VJ.mov"; //QString::fromStdString(transferEvent.GetDestinationPaths().at(0));
	//std::streamsize s;

	//int count = 0;

	_hashGenerator->Initialize();

	try
	{
		std::ifstream fin(_fileName, std::ios::in | std::ifstream::binary);
		//fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		if (!fin.is_open())
		{
			return;
		}

		int fileSize = GetFileSize(fin);
		
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
			//fout.write(buffer.data(), bufferSize);
		}

        uint64_t fileHash = _hashGenerator->Retrieve();
        OC_LOG_INFO("File: " + _fileName + " Hash: " + std::to_string(fileHash));
        if(fileHash != _checkSum)
        {
            OC_LOG_ERROR("Checksum not equal");
        }
        else
        {
            OC_LOG_INFO("Checksum OK");
        }

		emit HashChecked(fileHash);
	}
	catch (const std::ios_base::failure& e)
	{
		// TODO: Just debug code, replace with logging
		std::cout << e.what() << '\n';
		std::string ex = e.what();
	}
}
