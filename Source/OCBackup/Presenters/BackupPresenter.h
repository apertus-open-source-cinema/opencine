#ifndef BACKUPPRESENTER_H
#define BACKUPPRESENTER_H

#include <QFileSystemModel>
#include <QObject>
#include <QStringListModel>
#include <QFileSystemWatcher>
#include <QItemSelection>

#include <vector>
#include <functional>

//std::function<std::vector<std::string>()> GetMounts;

//#if defined(Q_OS_WIN)
//std::vector<std::string> GetMountsWindows()
//{
//}
//#elif defined (Q_OS_LINUX)

//#include <QMessageBox>
//#include <mntent.h>

//std::vector<std::string> GetMountsLinux()
//{
//    std::vector<std::string> mountPoints;

//    QString mediaFolder = "/media/" + qgetenv("USER") + "/";
//    QDirIterator directories(mediaFolder, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::NoIteratorFlags);

//    while(directories.hasNext())
//    {
//        directories.next();

//        mountPoints.push_back(QString(mediaFolder + directories.fileName()).toStdString());//drive->mnt_dir);
//    }

//    return mountPoints;
//}
//#else
//#error "OS not supported yet."
//#endif

//#include "Core/Context.h"
//#include "Model/FileInfo.h"

class IBackupPresenter
{
};

class BackupPresenter : public IBackupPresenter //: public QObject
{
//  Q_OBJECT

//public:
//  BackupPresenter(OCContext* context);
//  ~BackupPresenter();

//  QStringListModel* GetDriveListModel();
//  QFileSystemModel* GetFolderTreeModel();
//  std::vector<FileInfo*> GetFileList();

//  void SetMasterPath(QString path);

//  void TransferData();

//public slots:
//  void CurrentDriveChanged(const QModelIndex& current, const QModelIndex& previous);
//  void CurrentFolderChanged(const QItemSelection& current, const QItemSelection& previous);

//signals:
//  void DriveSelectionChanged(QModelIndex diveRoot);
//  void FolderChanged(std::vector<FileInfo*> fileList);

//private slots:
//  void UpdateMounts();
//private:
//  std::vector<std::string> GetMounts();
//  QStringList GetPathContent(QString path, QStringList& list);

//  std::vector<FileInfo*> _fileInfoList;

//  OCContext* _context;
//  OCSession* _session;

//  QString _currentDrivePath;

//  QFileSystemWatcher* _fileWatcher;

//  QStringListModel* _driveListModel;
//  QFileSystemModel* _folderTreeModel;

//  std::vector<QString> _backupPaths;
};

#endif // BACKUPPRESENTER_H
