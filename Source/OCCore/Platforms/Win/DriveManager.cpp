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

std::vector<DriveInfo> DriveManager::GetRemovableDrives()
{
	std::vector<std::string> availableDrives;
	std::vector<DriveInfo> removableDrives;

	DWORD dwSize = MAX_PATH;
	char szLogicalDrives[MAX_PATH] = { 0 };
	GetLogicalDriveStrings(dwSize, szLogicalDrives);

	char* disk = szLogicalDrives;
	while (*disk)
	{
		availableDrives.push_back(disk);

		disk = disk + strlen(disk) + 1;
	}

	EnumerateRemovableDrives(availableDrives, removableDrives);

	for (auto& drive : removableDrives)
	{
		RetrieveDriveInfo(drive);
	}

	return removableDrives;
}

void DriveManager::UpdateDriveList()
{
	emit DriveListChanged(GetRemovableDrives());
}

void DriveManager::EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<DriveInfo>& removableDrives)
{
	for (auto& drive : availableDrives)
	{
		int driveType = GetDriveType(drive.c_str());
		bool validVolume = GetVolumeInformation(drive.c_str(), NULL, 0, 0, 0, 0, NULL, 0);

		//        if(driveType == DRIVE_REMOVABLE && validVolume)
		//        {
		DriveInfo driveInfo;
		driveInfo.DrivePath = drive;

		RetrieveDriveInfo(driveInfo);

		removableDrives.push_back(driveInfo);
		//}
	}
}

void DriveManager::RetrieveDriveInfo(DriveInfo &driveInfo)
{
	unsigned __int64 freeBytesAvailable = 0;
	unsigned __int64 totalNumberOfBytes = 0;
	unsigned __int64 totalNumberOfFreeBytes = 0;
	GetDiskFreeSpaceEx(driveInfo.DrivePath.c_str(), (PULARGE_INTEGER)&freeBytesAvailable, (PULARGE_INTEGER)&totalNumberOfBytes, (PULARGE_INTEGER)&totalNumberOfFreeBytes);

	driveInfo.TotalSpace = totalNumberOfBytes / 1024 / 1024;
	driveInfo.UsedSpace = (totalNumberOfBytes - totalNumberOfFreeBytes) / 1024 / 1024;

	driveInfo.SpaceUnit = "MB";

	char volumeName[MAX_PATH];
	GetVolumeInformation(driveInfo.DrivePath.c_str(), volumeName, MAX_PATH, NULL, NULL, NULL, { 0 }, 0);
	driveInfo.DriveName = volumeName;
}