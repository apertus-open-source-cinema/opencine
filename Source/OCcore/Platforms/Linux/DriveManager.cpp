// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

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

std::vector<PathInfo> DriveManager::GetRemovableDrives()
{
    std::vector<PathInfo> availableDrives;

    QDirIterator directories(mediaFolder, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::NoIteratorFlags);

    while(directories.hasNext())
    {
        directories.next();

        PathInfo PathInfo;
        PathInfo.DriveName = directories.fileName().toStdString();

        PathInfo.DrivePath = QString(mediaFolder + directories.fileName()).toStdString();

        RetrievePathInfo(PathInfo);

        availableDrives.push_back(PathInfo);
    }

    return availableDrives;
}

void DriveManager::UpdateDriveList()
{
    emit DriveListChanged(GetRemovableDrives());
}

void DriveManager::RetrievePathInfo(PathInfo& PathInfo)
{
    //HACK: Used to to give Linux some time while mounting new drives is in progress
    usleep(500000);

    struct statvfs64 fiData;

    if(statvfs64(PathInfo.DrivePath.c_str(), &fiData) < 0)
    {
        return;
    }

    PathInfo.TotalSpace = (fiData.f_blocks * fiData.f_frsize) / 1024 / 1024;
    PathInfo.UsedSpace = PathInfo.TotalSpace - ((fiData.f_bfree * fiData.f_frsize) / 1024 / 1024);
    PathInfo.SpaceUnit = "MB";
}
