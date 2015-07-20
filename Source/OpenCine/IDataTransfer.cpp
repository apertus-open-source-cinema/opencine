#include "IDataTransfer.h"

#include <thread>
#include <future>
#include <fstream>

//#include <experimental/filesystem>

void DriveTransfer::CopyFiles()
{
    QDirIterator fileIterator(_sourcePath, QDir::NoDotAndDotDot | QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    unsigned int currentFileIndex = 0;
    while (fileIterator.hasNext())
    {
        if(fileIterator.filePath() != "")
        {
            QString path = fileIterator.filePath();
            QString relativePath = path.mid(_sourcePath.length());

            std::ifstream src(path.toStdString().c_str(), std::ios::binary);
            std::string relPath(_targetPath.toStdString().c_str());
            relPath += relativePath.toStdString().c_str();
            std::ofstream dst(relPath, std::ios::binary);

            dst << src.rdbuf();

            currentFileIndex++;
            emit ProgressChanged(currentFileIndex);
        }

        fileIterator.next();
    }
}
