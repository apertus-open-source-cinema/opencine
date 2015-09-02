#ifndef DRIVEMANAGER_H
#define DRIVEMANAGER_H

#include <string>
#include <vector>

#include "Interfaces/IDriveManager.h"

class EXPORT_API DriveManager : public IDriveManager
{
    Q_OBJECT

    std::vector<std::string> GetRemovableDrives();
    void EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<std::string>& removableDrives);

public slots:
    void UpdateDriveList();

public:
    DriveManager();
    ~DriveManager() {}

    void RequestDriveList();
};

#endif //DRIVEMANAGER_H
