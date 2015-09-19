#include "DriveManager.h"

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

std::vector<DriveInfo> DriveManager::GetRemovableDrives()
{
  std::vector<DriveInfo> availableDrives;

  QDirIterator directories(mediaFolder, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::NoIteratorFlags);

  while(directories.hasNext())
    {
      DriveInfo driveInfo;

      directories.next();

      driveInfo.DrivePath = QString(mediaFolder + directories.fileName()).toStdString();
      availableDrives.push_back(driveInfo);
    }

  return availableDrives;
}

void DriveManager::UpdateDriveList()
{
  emit DriveListChanged(GetRemovableDrives());
}

void DriveManager::RetrieveDriveInfo(DriveInfo& driveInfo)
{

}
