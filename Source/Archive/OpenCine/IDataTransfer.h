#ifndef IDATATRANSFER_H
#define IDATATRANSFER_H

#include <QDirIterator>

class IDataTransfer :  public QObject
{
    Q_OBJECT

protected:
    QString _sourcePath;
    QString _targetPath;

public:
    IDataTransfer(QWidget* parent = 0, QString sourcePath = "", QString targetPath = "") :
        _sourcePath(sourcePath),
        _targetPath(targetPath)
    {
    }

    QString GetSourcePath()
    {
        return _sourcePath;
    }

    QString GetTargetPath()
    {
        return _targetPath;
    }

    virtual void StartTransfer() = 0;
    virtual int GetCount() = 0;

signals:
    void ProgressChanged(int);
};

class DriveTransfer : public IDataTransfer
{
    Q_OBJECT

    void CreateDirectoryStructure()
    {
        QDirIterator dirIterator(_sourcePath, QDir::NoDotAndDotDot | QDir::Dirs | QDir::NoSymLinks, QDirIterator::Subdirectories);

        while (dirIterator.hasNext())
        {
            if(dirIterator.filePath() != "")
            {
                QString path = dirIterator.filePath();
                QString relativePath = path.mid(_sourcePath.length());

                QDir targetDir(_targetPath + relativePath);
                targetDir.mkpath(".");
            }

            dirIterator.next();
        }
    }

    void CopyFiles();

public:

    DriveTransfer(QWidget* parent = nullptr, QString sourcePath = "", QString targetPath = "") : IDataTransfer(parent, sourcePath, targetPath)
    {
    }

    void StartTransfer()
    {
        CreateDirectoryStructure();

        CopyFiles();
    }

    int GetCount()
    {
        return 0;
    }

signals:
    void ProgressChanged(int);

};

#endif // IDATATRANSFER_H

