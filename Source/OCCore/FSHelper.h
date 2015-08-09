#ifndef FSHELPER_H
#define FSHELPER_H

#include <string>
#include <vector>

#include <QAbstractNativeEventFilter>

#include "Interfaces/IDriveManager.h"

class NativeEventFilter : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    virtual bool nativeEventFilter(const QByteArray& eventType, void* message, long* result );

signals:
    void DeviceInserted();
    void DeviceRemoved();
};

class EXPORT_API DriveManager : public IDriveManager
{
    Q_OBJECT

    NativeEventFilter *_filter;

    std::vector<std::string> GetRemovableDrives();
    void EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<std::string>& removableDrives);

    void UpdateDriveList();

public:
    DriveManager();
    ~DriveManager() {}

    void RequestDriveList();
};

#endif //FSHELPER_H
