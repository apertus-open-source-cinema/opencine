#include "NativeEventHelper.h"

NativeEventFilter::NativeEventFilter()
{
    dummyWidget = std::make_shared<QWidget>();
    LPITEMIDLIST itemList;

    if(SHGetFolderLocation((HWND)dummyWidget->winId(), CSIDL_DESKTOP, 0, 0, &itemList) == NOERROR)
    {
        SHChangeNotifyEntry notifyEntry;
        notifyEntry.pidl = itemList;
        notifyEntry.fRecursive = TRUE;

        notifyID = SHChangeNotifyRegister((HWND)dummyWidget->winId(), SHCNRF_ShellLevel, SHCNE_MEDIAINSERTED | SHCNE_MEDIAREMOVED, WM_USER_MEDIACHANGED, 1, &notifyEntry);
    }
}

NativeEventFilter::~NativeEventFilter()
{
    SHChangeNotifyDeregister(notifyID);
}

bool NativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;

    if (msg->message == WM_DEVICECHANGE)
    {
        switch(msg->wParam)
        {
        case DBT_DEVICEARRIVAL:
            emit DeviceInserted();
            return true;
        case DBT_DEVICEREMOVECOMPLETE:
            emit DeviceRemoved();
            break;
        }
    }
    else if(msg->message == WM_USER_MEDIACHANGED)
    {
        emit DeviceInserted();
    }

    return false;
}
