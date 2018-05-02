// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IBACKUPVIEW_H
#define IBACKUPVIEW_H

#include <QWidget>

#include <Interfaces/IDriveManager.h>

#include <MVP/IView.h>

#include <Transfer/ItemInfo.h>

class IBackupView : public IView
{
	Q_OBJECT

public:
    virtual void SetDriveList(std::vector<PathInfo> driveList) = 0;
	virtual void SetCurrentFolder(QString folderPath) = 0;
    virtual void SetItemList(std::vector<FileInfo> fileList) = 0;
    virtual void SetDestinationList(std::vector<PathInfo> destinationList) = 0;

    virtual void OpenClip(QString clipPath) = 0;

signals:
	void StartTransfer();

	void DriveSelectionChanged(int driveIndex);
	void FolderSelectionChanged(QString folderPath);

	void AddDestinationClicked();

    void LoadClip(int clipIndex);
};

#endif //IBACKUPVIEW_H
