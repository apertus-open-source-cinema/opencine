#include "FSHelper.h"

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
        if(GetDriveType(drive.c_str()) == DRIVE_REMOVABLE)
        {
            removableDrives.push_back(drive);
        }
    }
}

bool NativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;

    if (msg->message == WM_DEVICECHANGE)
    {
        switch(msg->wParam)
        {
        case DBT_DEVICEARRIVAL: // never comes here!
            emit DeviceInserted();
            return true;
        case DBT_DEVICEREMOVECOMPLETE:
            emit DeviceRemoved();
            break;
        }
    }

    return false;
}
