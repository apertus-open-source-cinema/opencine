#include "BackupPresenter.h"

//#include "ProgressDialog.h"

//#include <thread>

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

//BackupPresenter::BackupPresenter(OCContext *context) :
//    _context(context),
//    _currentDrivePath("")
//{
//    //Setup drive list model
//    QStringList stringList;
//    for(std::string drive : GetMountsLinux())
//    {
//        stringList.push_back(QString::fromStdString(drive));
//    }

//    _driveListModel = new QStringListModel();
//    _driveListModel->setStringList(stringList);

//    //Setup folder tree model
//    _folderTreeModel = new QFileSystemModel();
//    QString rootPath = _driveListModel->index(0).data().toString();
//    _folderTreeModel->setRootPath(rootPath);
//    _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

//    _fileWatcher = new QFileSystemWatcher();
//    QString mediaFolder = "/media/" + qgetenv("USER") + "/";
//    _fileWatcher->addPath(mediaFolder);

//    QObject::connect(_fileWatcher, SIGNAL(directoryChanged(QString)), SLOT(UpdateMounts()));
//}

//BackupPresenter::~BackupPresenter()
//{

//}

//QStringListModel* BackupPresenter::GetDriveListModel()
//{
//    return _driveListModel;
//}

//QFileSystemModel* BackupPresenter::GetFolderTreeModel()
//{
//    return _folderTreeModel;
//}

//std::vector<FileInfo*> BackupPresenter::GetFileList()
//{
//    _fileInfoList.push_back(new FileInfo("test1234", "NAME", 256, 192, 29.93));
//    return _fileInfoList;
//}

//void BackupPresenter::SetMasterPath(QString path)
//{
//    if(_backupPaths.empty())
//    {
//        _backupPaths.push_back(QString(path));
//    }
//    else
//    {
//        _backupPaths.at(0) = QString(path);
//    }
//}

////Reference: http://stackoverflow.com/questions/2536524/copy-directory-using-qt
//QStringList BackupPresenter::GetPathContent(QString path, QStringList& list)
//{
//    QDir targetDir(path);
//    QDirIterator it(path, QDir::NoDotAndDotDot | QDir::Dirs | QDir::NoSymLinks, QDirIterator::Subdirectories);

//    QString entryPath = "";

//    while (it.hasNext())
//    {
//        QFileInfo fileInfo = it.fileInfo();

//        if(fileInfo.filePath() != "")
//        {
//            entryPath = QString(targetDir.relativeFilePath(fileInfo.absoluteFilePath()));
//            list.push_back(entryPath);
//        }
//        it.next();
//    }
//}

//void BackupPresenter::TransferData()
//{
//    if(_backupPaths.empty() || _backupPaths.at(0) == "")
//    {
//        QMessageBox messageBox;
//        messageBox.setText("Master path is not set.");
//        messageBox.exec();
//        return;
//    }

//    IDataTransfer* driveTransfer = new DriveTransfer(nullptr, _currentDrivePath, _backupPaths[0]);
//    ProgressDialog progressDialog(nullptr, driveTransfer);

//    // Start copying files in separate thread, possibly mutex required for progress data
//    std::thread thr(&IDataTransfer::StartTransfer, driveTransfer);
//    thr.detach();

//    progressDialog.exec();
//}

//std::vector<std::string> BackupPresenter::GetMounts()
//{
//    return GetMountsLinux();
//}

//void BackupPresenter::UpdateMounts()
//{
//    //Setup drive list model
//    QStringList stringList;

//    //Needs rework for multi-platform
//    for(std::string drive : GetMountsLinux())
//    {
//        stringList.push_back(QString::fromStdString(drive));
//    }

//    _driveListModel->setStringList(stringList);
//}

//void BackupPresenter::CurrentDriveChanged(const QModelIndex& current, const QModelIndex& previous)
//{
//    _currentDrivePath = current.data().toString();
//    QModelIndex index = _folderTreeModel->setRootPath(_currentDrivePath);
//    emit DriveSelectionChanged(index);
//}

//void BackupPresenter::CurrentFolderChanged(const QItemSelection &current, const QItemSelection &previous)
//{
//    QString path = _folderTreeModel->filePath(current.indexes().at(0));
//    QDirIterator it(path, QDirIterator::NoIteratorFlags);
//    _fileInfoList.clear();
//    while (it.hasNext())
//    {
//        if(it.fileInfo().isFile())
//        {
//            _fileInfoList.push_back(new FileInfo(it.filePath(), it.fileName(), 100, 120, 23.95));
//        }
//        it.next();
//    }

//    emit FolderChanged(_fileInfoList);
//}


//void BackupPresenter::RefreshDriveList()
//{
//    IDriveManager* driveManager = new DriveManager();
//    std::vector<std::string> driveList = driveManager->GetRemovableDrives();

//    emit DriveListChanged(driveList);
//}

//void BackupPresenter::SelectDrive(std::string drivePath)
//{
//    int i = 0;
//}

//void BackupPresenter::StartTransfer()
//{
//    int i = 0;
//}

BackupPresenter::BackupPresenter(IBackupView &view) :
    _view(&view)
{
    _driveManager = new DriveManager();

    SetupSignals();

    _driveManager->RequestDriveList();
}

void BackupPresenter::SetupSignals()
{
    connect(_view, &IBackupView::StartTransfer, this, &BackupPresenter::StartTransfer);
    //connect(_driveManager, &IDriveManager::DriveListChanged, this, &BackupPresenter::DriveListChanged);
    connect(_driveManager, SIGNAL(DriveListChanged(std::vector<std::string>)), this, SLOT(DriveListChanged(std::vector<std::string>)));
    connect(_view, SIGNAL(DriveSelectionChanged(int)), this, SLOT(DriveSelectionChanged(int)));
}

void BackupPresenter::StartTransfer()
{
    int i = 0;
}

void BackupPresenter::DriveListChanged(std::vector<std::string> driveList)
{
    _driveList = driveList;
    _view->SetDriveList(_driveList);

    if(!_driveList.empty())
    {
        _view->SetCurrentFolder(_driveList.at(0));
    }
    else
    {
        _view->SetCurrentFolder("");
    }
}

void BackupPresenter::DriveSelectionChanged(int driveIndex)
{
    _view->SetCurrentFolder(_driveList.at(driveIndex));
}
