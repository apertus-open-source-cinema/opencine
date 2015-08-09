#ifndef IBACKUPVIEW_H
#define IBACKUPVIEW_H

//#include <MVP/MVP.h>

#include <QWidget>

class IBackupView : public QWidget
{
    Q_OBJECT

public:
    virtual void SetDriveList(std::vector<std::string> driveList) = 0;

signals:
    void StartTransfer();
    void DriveSelectionChanged();
    void FolderSelectionChanged();
};

#endif //IBACKUPVIEW_H
