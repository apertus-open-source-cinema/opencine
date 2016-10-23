#ifndef DRIVETRANSFERSERVICE_H
#define DRIVETRANSFERSERVICE_H

#include "OCService.h"
#include <Task/ITaskProgress.h>


// TODO: Refactor by moving to more suitable location and possibly renaming, possible location OCCore
// Note: std::string is used instead of QString, see previous note
class IDriveTransferService : public OCService, public ITaskProgress
{
public:
    virtual ~IDriveTransferService() {}

    virtual void SetSourceDrive(std::string sourceDrive) = 0;
    virtual void SetDestinationDrives(std::vector<std::string> destinationDrives) = 0;
};

class DriveTransferService : public IDriveTransferService
{
public:
    virtual void SetSourceDrive(std::string sourceDrive) override
    {

    }

    virtual void SetDestinationDrives(std::vector<std::string> destinationDrives) override
    {

    }

    bool Execute()
    {
        bool finished = false;

        return finished;
    }

	int GetProgressPercentage() override { return 0; }
	std::string GetTaskDescription() override { return ""; }
	std::string GetSubTaskDescription() override { return ""; }
};

#endif //DRIVETRANSFERSERVICE_H
