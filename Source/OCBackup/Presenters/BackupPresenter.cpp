#include "BackupPresenter.h"

#include <QFileDialog>
#include <QTreeView>
#include <QDebug>
#include <QFileInfoList>

#include <DriveManager.h>

BackupPresenter::BackupPresenter(IBackupView &view) : BasePresenter(),
    _view(&view)
{
    _driveManager = new DriveManager();

    SetupSignals();

    _driveManager->RequestDriveList();
}

void BackupPresenter::SetupSignals() const
{
    connect(_driveManager, SIGNAL(DriveListChanged(std::vector<PathInfo>)), this, SLOT(DriveListChanged(std::vector<PathInfo>)));
    connect(_view, SIGNAL(DriveSelectionChanged(int)), this, SLOT(DriveSelectionChanged(int)));

    connect(_view, &IBackupView::AddDestinationClicked, this, &BackupPresenter::AddDestination);
    connect(_view, &IBackupView::FolderSelectionChanged, this, &BackupPresenter::FolderSelectionChanged);
    connect(_view, &IBackupView::StartTransfer, this, &BackupPresenter::StartTransfer);
}

void BackupPresenter::StartTransfer() const
{
    //emit StartTransferSig("/media/andi/OC_TEST_MSD");
}

void BackupPresenter::DriveListChanged(std::vector<PathInfo> driveList)
{
    _driveList = driveList;
    _view->SetDriveList(driveList);

    if (!_driveList.empty())
    {
        QString drive = QString::fromStdString(driveList.at(0).DrivePath);
        _view->SetCurrentFolder(drive);

        FolderSelectionChanged(drive);
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

    FolderSelectionChanged(folderPath);
}

//std::vector<DestinationsListItem> _destinationList;

void BackupPresenter::AddDestination() const
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
        //_destinationList.push_back(directory);
        //DestinationsListItem destination(directory, "", 0, 0, "Test");
        //_destinationList.push_back(destination);

        //_view->SetDestinationList(_destinationList);
        qDebug() << directory;
    }
}

void BackupPresenter::FolderSelectionChanged(QString folderPath) const
{
    QDir dir(folderPath);
    QFileInfoList fileList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);

    std::vector<FileInfo> fileInfoList;

    for (QFileInfo fileInfo : fileList)
    {
        FileInfo info(fileInfo.path(), fileInfo.fileName(), fileInfo.size());
        fileInfoList.push_back(info);
    }

    _view->SetItemList(fileInfoList);
}
