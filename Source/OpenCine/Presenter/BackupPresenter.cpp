#include "BackupPresenter.h"

std::function<std::vector<std::string>()> GetMounts;

#if defined(Q_OS_WIN)
std::vector<std::string> GetMountsWindows()
{
}
#elif defined (Q_OS_LINUX)
#include <mntent.h>

std::vector<std::string> GetMountsLinux()
{
    std::vector<std::string> mountPoints;

    QString mediaFolder = "/media/" + qgetenv("USER") + "/";
    QDirIterator directories(mediaFolder, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::NoIteratorFlags);

    while(directories.hasNext())
    {
        directories.next();


        mountPoints.push_back(QString(mediaFolder + directories.fileName()).toStdString());//drive->mnt_dir);
        //all_dirs << directories.filePath();
    }

    /*FILE* file = setmntent("/etc/mtab", "r");

    mntent* drive;
    do
    {
        drive = getmntent(file);

        if(drive != nullptr && std::string(drive->mnt_dir).find("/media") == 0)
        {
            mountPoints.push_back(drive->mnt_dir);
        }
    }while(drive != nullptr);

    //mountPoints.push_back("/");
    int i = 0;*/

    return mountPoints;
}
#else
#error "OS not supported yet."
#endif

BackupPresenter::BackupPresenter(OCContext *context) :
    _context(context)
{
    //Setup drive list model
    QStringList stringList;
    for(std::string drive : GetMountsLinux())
    {
        stringList.push_back(QString::fromStdString(drive));
    }

    _driveListModel = new QStringListModel();
    _driveListModel->setStringList(stringList);

    //Setup folder tree model
    _folderTreeModel = new QFileSystemModel();
    QString rootPath = _driveListModel->index(0).data().toString();
    _folderTreeModel->setRootPath(rootPath);
    _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

    _fileWatcher = new QFileSystemWatcher();
    QString mediaFolder = "/media/" + qgetenv("USER") + "/";
    _fileWatcher->addPath(mediaFolder);

    QObject::connect(_fileWatcher, SIGNAL(directoryChanged(QString)), SLOT(UpdateMounts()));
}

BackupPresenter::~BackupPresenter()
{

}

QStringListModel* BackupPresenter::GetDriveListModel()
{
    return _driveListModel;
}

QFileSystemModel* BackupPresenter::GetFolderTreeModel()
{
    return _folderTreeModel;
}

std::vector<std::string> BackupPresenter::GetMounts()
{
    return GetMountsLinux();
}

void BackupPresenter::UpdateMounts()
{
    //Setup drive list model
    QStringList stringList;
    for(std::string drive : GetMountsLinux())
    {
        stringList.push_back(QString::fromStdString(drive));
    }

    _driveListModel->setStringList(stringList);
}

void BackupPresenter::CurrentDriveChanged(const QModelIndex& current, const QModelIndex& previous)
{
    QString rootPath = current.data().toString();
    QModelIndex index = _folderTreeModel->setRootPath(rootPath);
    emit DriveSelectionChanged(index);
}
