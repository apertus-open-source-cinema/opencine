#include "DriveManager.h"

#include <memory>
#include <sys/statvfs.h>
#include <unistd.h>

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
        directories.next();

        DriveInfo driveInfo;
        driveInfo.DriveName = directories.fileName().toStdString();

        driveInfo.DrivePath = QString(mediaFolder + directories.fileName()).toStdString();

        RetrieveDriveInfo(driveInfo);

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
    //HACK: Used to to give Linux some time while mounting new drives is in progress
    usleep(500000);

    struct statvfs64 fiData;

    if(statvfs64(driveInfo.DrivePath.c_str(), &fiData) < 0)
    {
        return;
    }

    driveInfo.TotalSpace = (fiData.f_blocks * fiData.f_frsize) / 1024 / 1024;
    driveInfo.UsedSpace = driveInfo.TotalSpace - ((fiData.f_bfree * fiData.f_frsize) / 1024 / 1024);
    driveInfo.SpaceUnit = "MB";
}
