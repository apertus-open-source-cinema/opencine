#include "DriveManager.h"

#include <string>
#include <vector>
#include <memory>

#include <windows.h>
#include <dbt.h>

#include <QWidget>
#include <QDebug>
#include <QAbstractEventDispatcher>

#include "NativeEventHelper.h"

std::shared_ptr<NativeEventFilter> nativeEventFilter;

DriveManager::DriveManager()
{
    nativeEventFilter = std::make_shared<NativeEventFilter>();
    QAbstractEventDispatcher::instance()->installNativeEventFilter(nativeEventFilter.get());

    connect(nativeEventFilter.get(), &NativeEventFilter::DeviceInserted, this, &DriveManager::UpdateDriveList);
    connect(nativeEventFilter.get(), &NativeEventFilter::DeviceRemoved, this, &DriveManager::UpdateDriveList);
}

void DriveManager::RequestDriveList()
{
    UpdateDriveList();
}

std::vector<std::string> DriveManager::GetRemovableDrives()
{
    std::vector<std::string> availableDrives;
    std::vector<std::string> removableDrives;

    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};
    GetLogicalDriveStrings(dwSize,szLogicalDrives);

    char* disk = szLogicalDrives;
    while (*disk)
    {
        availableDrives.push_back(disk);

        disk = disk + strlen(disk) + 1;
    }

    EnumerateRemovableDrives(availableDrives, removableDrives);

    return removableDrives;
}

void DriveManager::UpdateDriveList()
{
    emit DriveListChanged(GetRemovableDrives());
}

void DriveManager::EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<std::string>& removableDrives)
{
    for(auto& drive : availableDrives)
    {
        int driveType = GetDriveType(drive.c_str());
        bool validVolume = GetVolumeInformation(drive.c_str(), NULL, 0, 0, 0, 0, NULL, 0);

        if(driveType == DRIVE_REMOVABLE && validVolume)
        {
            unsigned __int64 freeBytesAvailable = 0;
            unsigned __int64 totalNumberOfBytes = 0;
            unsigned __int64 totalNumberOfFreeBytes = 0;
            GetDiskFreeSpaceEx(drive.c_str(), (PULARGE_INTEGER)&freeBytesAvailable, (PULARGE_INTEGER)&totalNumberOfBytes, (PULARGE_INTEGER)&totalNumberOfFreeBytes);

            removableDrives.push_back(drive);
        }
    }
}


