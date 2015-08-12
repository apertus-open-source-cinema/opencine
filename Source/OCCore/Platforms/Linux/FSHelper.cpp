#include "FSHelper.h"

#include <memory>

#include <QDirIterator>
#include <QFileSystemWatcher>

std::shared_ptr<QFileSystemWatcher> fileWatcher;
QString mediaFolder = "/media/" + qgetenv("USER") + "/";

DriveManager::DriveManager()
{
  fileWatcher = std::make_shared<QFileSystemWatcher>();
  fileWatcher->addPath(mediaFolder);

  QObject::connect(fileWatcher.get(), SIGNAL(directoryChanged(QString)), SLOT(UpdateDriveList()));
}

void DriveManager::RequestDriveList()
{
  UpdateDriveList();
}

std::vector<std::string> DriveManager::GetRemovableDrives()
{
  std::vector<std::string> availableDrives;

  QDirIterator directories(mediaFolder, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::NoIteratorFlags);

  while(directories.hasNext())
    {
      directories.next();

      availableDrives.push_back(QString(mediaFolder + directories.fileName()).toStdString());//drive->mnt_dir);
    }

  return availableDrives;
}

void DriveManager::UpdateDriveList()
{
  emit DriveListChanged(GetRemovableDrives());
}
