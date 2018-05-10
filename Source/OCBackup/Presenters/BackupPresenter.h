// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

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

private slots:
	void DriveListChanged(std::vector<PathInfo> driveList);
	void DriveSelectionChanged(int driveIndex);
	void AddDestination();
	void FolderSelectionChanged(QString folderPath) const;

    void LoadClip(int clipIndex) const;

public:
	explicit BackupPresenter(IBackupView& view, OCEventBus* eventBus);
	void receive(const OCEvent& event) const;
};

#endif // BACKUPPRESENTER_H
