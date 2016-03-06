#ifndef IDATATRANSFER_H
#define IDATATRANSFER_H

#include <string>

class IDataTransfer
{
protected:
    std::string _sourcePath;
    std::string _targetPath;

public:
    IDataTransfer(std::string sourcePath = "", std::string targetPath = "") :
        _sourcePath(sourcePath),
        _targetPath(targetPath)
    {
    }

//    QString GetSourcePath()
//    {
//        return _sourcePath;
//    }

//    QString GetTargetPath()
//    {
//        return _targetPath;
//    }

    virtual void StartTransfer() = 0;
    //virtual int GetCount() = 0;

//signals:
//    void ProgressChanged(int);
};

#endif // IDATATRANSFER_H

