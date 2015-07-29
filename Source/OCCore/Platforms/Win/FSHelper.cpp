#include "FSHelper.h"

#include <string>
#include <vector>

#include <windows.h>

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

