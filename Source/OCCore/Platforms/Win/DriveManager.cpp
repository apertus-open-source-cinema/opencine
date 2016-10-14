#include "DriveManager.h"

#include <vector>
#include <memory>

#include <windows.h>
#include <dbt.h>

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

std::vector<PathInfo> DriveManager::GetRemovableDrives()
{
	std::vector<std::string> availableDrives;
	std::vector<PathInfo> removableDrives;

	DWORD dwSize = MAX_PATH;
	char szLogicalDrives[MAX_PATH] = {0};
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
		RetrievePathInfo(drive);
	}

	return removableDrives;
}

void DriveManager::UpdateDriveList()
{
	emit DriveListChanged(GetRemovableDrives());
}

void DriveManager::EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<PathInfo>& removableDrives)
{
	for (auto& drive : availableDrives)
	{
		int driveType = GetDriveType(drive.c_str());
		bool validVolume = GetVolumeInformation(drive.c_str(), nullptr, 0, nullptr, nullptr, nullptr, nullptr, 0);

		//        if(driveType == DRIVE_REMOVABLE && validVolume)
		//        {
		PathInfo driveInfo;
		driveInfo.DrivePath = drive;

		RetrievePathInfo(driveInfo);

		removableDrives.push_back(driveInfo);
		//}
	}
}

void DriveManager::RetrievePathInfo(PathInfo& driveInfo)
{
	unsigned __int64 freeBytesAvailable = 0;
	unsigned __int64 totalNumberOfBytes = 0;
	unsigned __int64 totalNumberOfFreeBytes = 0;
	GetDiskFreeSpaceEx(driveInfo.DrivePath.c_str(), reinterpret_cast<PULARGE_INTEGER>(&freeBytesAvailable), reinterpret_cast<PULARGE_INTEGER>(&totalNumberOfBytes), (PULARGE_INTEGER)&totalNumberOfFreeBytes);

	driveInfo.TotalSpace = totalNumberOfBytes / 1024 / 1024;
	driveInfo.UsedSpace = (totalNumberOfBytes - totalNumberOfFreeBytes) / 1024 / 1024;

	driveInfo.SpaceUnit = "MB";

	char volumeName[MAX_PATH];
	GetVolumeInformation(driveInfo.DrivePath.c_str(), volumeName, MAX_PATH, nullptr, nullptr, nullptr, {nullptr}, 0);
	driveInfo.DriveName = volumeName;
}
