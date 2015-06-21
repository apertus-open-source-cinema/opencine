#ifndef DATATRANSFERTESTS_H
#define DATATRANSFERTESTS_H

#include <memory>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "IDataTransfer.h"

class FileSystemHelper
{
 public:
    FileSystemHelper()
    {
    }

    bool RemoveDirectory(QString path, bool contentOnly)
    {
        bool result = false;

        //Remove contained directories from path
        RemoveDirectories(path);

        //Remove contained files from path
        RemoveFiles(path);

        if(!contentOnly)
        {
            QDir dir(path);
            result = dir.rmdir(dir.absolutePath());
        }

        return result;
    }

    bool RemoveDirectories(QString path)
    {
        bool result = false;

        QDirIterator fileIterator(path, QDir::NoDotAndDotDot | QDir::AllDirs | QDir::NoSymLinks, QDirIterator::NoIteratorFlags);

        while (fileIterator.hasNext())
        {
            fileIterator.next();

            QFileInfo fileInfo = fileIterator.fileInfo();

            if(fileInfo.isDir())
            {
                QDir dir(fileInfo.absoluteFilePath());
                result = dir.removeRecursively();
            }

            if (!result)
            {
                result = false;
                break;
            }
        }

        return result;
    }

    bool RemoveFiles(QString path)
    {
        bool result = false;

        QDirIterator fileIterator(path, QDir::NoDotAndDotDot | QDir::Files | QDir::NoSymLinks, QDirIterator::NoIteratorFlags);

        while (fileIterator.hasNext())
        {
            fileIterator.next();

            QFileInfo fileInfo = fileIterator.fileInfo();

            if(fileInfo.isFile())
            {
                QFile file(fileInfo.absoluteFilePath());
                result = file.remove();
            }

            if (!result)
            {
                result = false;
                break;
            }
        }

        return result;
    }
};

class DataTransferTests
{
    std::shared_ptr<FileSystemHelper> _fsHelper = std::make_shared<FileSystemHelper>();

public:
    DataTransferTests()
    {
        _fsHelper->RemoveDirectory("./UnitTests/Output", true);
    }
};

TEST_CASE_METHOD(DataTransferTests, "Copy folder structure")
{
    REQUIRE(false);
}

#endif // DATATRANSFERTESTS_H
