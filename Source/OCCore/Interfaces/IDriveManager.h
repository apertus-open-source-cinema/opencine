#ifndef IDRIVEMANAGER_H
#define IDRIVEMANAGER_H

#include <QObject>

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

struct EXPORT_API DriveInfo
{
    std::string DriveName;
    std::string DrivePath;
    unsigned __int64 UsedSpace;
    unsigned __int64 TotalSpace;
    std::string SpaceUnit;
};

class EXPORT_API IDriveManager : public QObject
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
