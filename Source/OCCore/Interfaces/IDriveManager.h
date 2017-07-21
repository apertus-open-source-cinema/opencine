// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IDRIVEMANAGER_H
#define IDRIVEMANAGER_H

#include <inttypes.h>

#include <QObject>

#include "../Transfer/PathInfo.h"

#include "OCCore_export.h"

class OCCORE_EXPORT IDriveManager : public QObject
{
	Q_OBJECT

public:
	virtual ~IDriveManager() {}
    virtual std::vector<PathInfo> GetRemovableDrives() = 0;
	virtual void RequestDriveList() = 0;
    virtual void RetrievePathInfo(PathInfo& PathInfo) = 0;

signals:
    void DriveListChanged(std::vector<PathInfo> driveList);
};

#endif //IDRIVEMANAGER_H
