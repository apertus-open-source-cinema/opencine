#include "BackupPresenter.h"

#include <QFileDialog>
#include <QTreeView>
#include <QDebug>

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

    connect(_view, &IBackupView::StartTransfer, this, &BackupPresenter::StartTransfer);
}

void BackupPresenter::StartTransfer()
{
    emit StartTransferSig("/media/andi/OC_TEST_MSD");
}

void BackupPresenter::DriveListChanged(std::vector<DriveInfo> driveList)
{
    _driveList = driveList;
    _view->SetDriveList(driveList);

    if(!_driveList.empty())
    {
        _view->SetCurrentFolder(driveList.at(0).DrivePath);

        std::vector<std::string> flist;
        flist.push_back("C:/Temp/test.jpg");
        _view->SetItemList(flist);
    }
    else
    {
        _view->SetCurrentFolder("");
    }
}

void BackupPresenter::DriveSelectionChanged(int driveIndex)
{
    if(_driveList.empty())
    {
        return;
    }

    _view->SetCurrentFolder(_driveList.at(driveIndex).DrivePath);
}

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
        qDebug()<<directory;
    }
}
