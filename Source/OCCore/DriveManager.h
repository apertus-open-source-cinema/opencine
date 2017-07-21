// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef DRIVEMANAGER_H
#define DRIVEMANAGER_H

#include <vector>

#include "Interfaces/IDriveManager.h"

class OCCORE_EXPORT DriveManager : public IDriveManager
{
    Q_OBJECT

    std::vector<PathInfo> GetRemovableDrives() override;
    void EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<PathInfo>& removableDrives);

public slots:
    void UpdateDriveList();

public:
    DriveManager();
    ~DriveManager() {}

    void RequestDriveList() override;
    void RetrievePathInfo(PathInfo &PathInfo) override;
};

#endif //DRIVEMANAGER_H
