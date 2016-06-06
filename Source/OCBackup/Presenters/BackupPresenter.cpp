#include "BackupPresenter.h"

#include <QFileDialog>
#include <QTreeView>
#include <QDebug>
#include <QFileInfoList>
#include <QQmlContext>

#include <DriveManager.h>

BackupPresenter::BackupPresenter(IBackupView &view) :
	_view(&view)
{
	_driveManager = new DriveManager();

	SetupSignals();

	_driveManager->RequestDriveList();
}

void BackupPresenter::SetupSignals()
{
	connect(_driveManager, SIGNAL(DriveListChanged(std::vector<DriveInfo>)), this, SLOT(DriveListChanged(std::vector<DriveInfo>)));
	connect(_view, SIGNAL(DriveSelectionChanged(int)), this, SLOT(DriveSelectionChanged(int)));

	connect(_view, &IBackupView::AddDestinationClicked, this, &BackupPresenter::AddDestination);

	connect(_view, &IBackupView::FolderSelectionChanged, this, &BackupPresenter::FolderSelectionChanged);

	connect(_view, &IBackupView::StartTransfer, this, &BackupPresenter::StartTransfer);
}

void BackupPresenter::StartTransfer()
{
	//emit StartTransferSig("/media/andi/OC_TEST_MSD");
}

void BackupPresenter::DriveListChanged(std::vector<DriveInfo> driveList)
{
	_driveList = driveList;
	_view->SetDriveList(driveList);

	if (!_driveList.empty())
	{
		QString drive = QString::fromStdString(driveList.at(0).DrivePath);
		_view->SetCurrentFolder(drive);

		/*std::vector<std::string> flist;
		flist.push_back("C:/Temp/test.jpg");
		_view->SetItemList(flist);*/
	}
	else
	{
		_view->SetCurrentFolder("");
	}
}

void BackupPresenter::DriveSelectionChanged(int driveIndex)
{
	if (_driveList.empty())
	{
		return;
	}

	QString folderPath = QString::fromStdString(_driveList.at(driveIndex).DrivePath);
	_view->SetCurrentFolder(folderPath);
}

std::vector<QString> _destinationList;

void BackupPresenter::AddDestination()
{
	QFileDialog dialog;
	dialog.setFileMode(QFileDialog::Directory);
	dialog.setOption(QFileDialog::ShowDirsOnly);
	dialog.setViewMode(QFileDialog::Detail);
	int result = dialog.exec();

	QString directory;
	if (result)
	{
		directory = dialog.selectedFiles()[0];
		_destinationList.push_back(directory);
		
		_view->SetDestinationList(_destinationList);
		qDebug() << directory;
	}
}

void BackupPresenter::FolderSelectionChanged(QString folderPath)
{
	QDir dir(folderPath);
	QFileInfoList fileList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);

	std::vector<QString> fileNameList;

	for (QFileInfo fileInfo : fileList)
	{
		fileNameList.push_back(fileInfo.filePath());
	}

	_view->SetItemList(fileNameList);
}