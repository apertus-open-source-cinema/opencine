#ifndef BACKUPPRESENTER_H
#define BACKUPPRESENTER_H

#include <vector>
#include <functional>

#include <QFileSystemModel>
#include <QObject>
#include <QStringListModel>
#include <QItemSelection>

#include <MVP/BasePresenter.h>

#include <Events/EventBus.h>

#include "../Interfaces/IBackupView.h"

//class IBackupPresenter : public QObject
//{
//	Q_OBJECT

//public:
//	//virtual void RefreshDriveList() = 0;
//	//virtual void SelectDrive(std::string drivePath) = 0;

//	//virtual void StartTransfer() = 0;

//signals:
//	//void DriveListChanged(std::vector<PathInfo> driveList);
//	//void DriveSelectionChanged(std::vector<std::string> driveList);
//};

class BackupPresenter : public OC::UI::BasePresenter
{
	Q_OBJECT

	IBackupView* _view;
	IDriveManager* _driveManager;

	unsigned int _currentDrive;

	std::vector<PathInfo> _driveList;
	std::vector<PathInfo> _destinationList;

	void SetupSignals() const;

	void StartTransfer();

	//signals:
	//void StartTransferSig(std::string drivePath);

private slots:
	void DriveListChanged(std::vector<PathInfo> driveList);
	void DriveSelectionChanged(int driveIndex);
	void AddDestination();
	void FolderSelectionChanged(QString folderPath) const;

public:
	explicit BackupPresenter(IBackupView& view, OCEventBus& eventBus);
	void receive(const OCEvent& event) const;
};

#endif // BACKUPPRESENTER_H
