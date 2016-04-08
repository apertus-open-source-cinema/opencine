#ifndef IDRIVEMANAGER_H
#define IDRIVEMANAGER_H

#include <inttypes.h>

#include <QObject>

#include "OCCore_export.h"

struct OCCORE_EXPORT DriveInfo
{
	std::string DriveName = "?";
	std::string DrivePath = "?";
	unsigned long long UsedSpace = 0;
	unsigned long long TotalSpace = 0;
	std::string SpaceUnit = "?";
};

class OCCORE_EXPORT IDriveManager : public QObject
{
	Q_OBJECT

public:
	virtual ~IDriveManager() {}
	virtual std::vector<DriveInfo> GetRemovableDrives() = 0;
	virtual void RequestDriveList() = 0;
	virtual void RetrieveDriveInfo(DriveInfo& driveInfo) = 0;

signals:
	void DriveListChanged(std::vector<DriveInfo> driveList);
};

#endif //IDRIVEMANAGER_H
