#ifndef FILEINFO_H
#define FILEINFO_H

class FileInfo
{
    // QString for now, as it's used primarily for UI
    QString _folderPath;
    QString _fileName;
    int64_t _sizeInBytes;

public:
    FileInfo(QString folderPath, QString fileName, unsigned int sizeInBytes)
    {
        _folderPath = folderPath;
        _fileName = fileName;
        _sizeInBytes = sizeInBytes;
    }

    QString GetFolderPath() const
    {
        return _folderPath;
    }

    QString GetFileName() const
    {
        return _fileName;
    }

    unsigned int GetSizeInBytes() const
    {
        return _sizeInBytes;
    }
};

#endif // FILEINFO_H
