#ifndef IBACKUPVIEW_H
#define IBACKUPVIEW_H

#include <QWidget>

#include <Interfaces/IDriveManager.h>

class IBackupView : public QWidget
{
	Q_OBJECT

public:
	virtual void SetDriveList(std::vector<DriveInfo> driveList) = 0;
	virtual void SetCurrentFolder(QString folderPath) = 0;
	virtual void SetItemList(std::vector<QString> fileList) = 0;

signals:
	void StartTransfer();

	void DriveSelectionChanged(int driveIndex);
	void FolderSelectionChanged(QString folderPath);

	void AddDestinationClicked();
};

#endif //IBACKUPVIEW_H
