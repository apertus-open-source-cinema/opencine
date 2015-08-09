#ifndef IDRIVEMANAGER_H
#define IDRIVEMANAGER_H

#include <QObject>

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

class EXPORT_API IDriveManager : public QObject
{
    Q_OBJECT

public:
    virtual ~IDriveManager() {}
    virtual std::vector<std::string> GetRemovableDrives() = 0;
    virtual void RequestDriveList() = 0;

signals:
    void DriveListChanged(std::vector<std::string> driveList);
};

#endif //IDRIVEMANAGER_H
