#ifndef DRIVEMANAGER_H
#define DRIVEMANAGER_H

#include <vector>

#include "Interfaces/IDriveManager.h"

class OCCORE_EXPORT DriveManager : public IDriveManager
{
	Q_OBJECT

		std::vector<DriveInfo> GetRemovableDrives() override;
	void EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<DriveInfo>& removableDrives);

	public slots:
	void UpdateDriveList();

public:
	DriveManager();
	~DriveManager() {}

	void RequestDriveList() override;
	void RetrieveDriveInfo(DriveInfo &driveInfo) override;
};

#endif //DRIVEMANAGER_H
