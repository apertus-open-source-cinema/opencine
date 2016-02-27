#ifndef DRIVEMANAGER_H
#define DRIVEMANAGER_H

#include <string>
#include <vector>

#include "Interfaces/IDriveManager.h"

class OCCORE_EXPORT DriveManager : public IDriveManager
{
    Q_OBJECT

    std::vector<DriveInfo> GetRemovableDrives();
    void EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<DriveInfo>& removableDrives);

public slots:
    void UpdateDriveList();

public:
    DriveManager();
    ~DriveManager() {}

    void RequestDriveList();
    void RetrieveDriveInfo(DriveInfo &driveInfo);
};

#endif //DRIVEMANAGER_H
