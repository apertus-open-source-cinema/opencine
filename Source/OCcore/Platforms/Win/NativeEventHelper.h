// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef NATIVEEVENTHELPER_H
#define NATIVEEVENTHELPER_H

#include <memory>

#include <shlobj.h>
#include <Dbt.h>

#include <QAbstractNativeEventFilter>
#include <QWidget>

#define WM_USER_MEDIACHANGED WM_USER+128

class NativeEventFilter : public QObject, public QAbstractNativeEventFilter
{
	Q_OBJECT

		std::shared_ptr<QWidget> dummyWidget;

	int notifyID;

public:
	virtual bool nativeEventFilter(const QByteArray& eventType, void* message, long* result);

	NativeEventFilter();
	~NativeEventFilter();

signals:
	void DeviceInserted();
	void DeviceRemoved();
};

#endif //NATIVEEVENTHELPER_H
