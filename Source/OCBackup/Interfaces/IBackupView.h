#ifndef IBACKUPVIEW_H
#define IBACKUPVIEW_H

//#include <MVP/MVP.h>

#include <QWidget>

class IBackupView : public QWidget
{
    Q_OBJECT

public:
    virtual void SetDriveList(std::vector<std::string> driveList) = 0;
    virtual void SetCurrentFolder(std::string folderPath) = 0;

signals:
    void StartTransfer();
    void DriveSelectionChanged(int driveIndex);
    void FolderSelectionChanged();
};

#endif //IBACKUPVIEW_H
