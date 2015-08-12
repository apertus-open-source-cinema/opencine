#ifndef NATIVEEVENTHELPER_H
#define NATIVEEVENTHELPER_H

#include <QAbstractNativeEventFilter>

class NativeEventFilter : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    virtual bool nativeEventFilter(const QByteArray& eventType, void* message, long* result );

signals:
    void DeviceInserted();
    void DeviceRemoved();
};

#endif //NATIVEEVENTHELPER_H
