#include "BackupView.h"
#include "ui_BackupView.h"

#include <QStringListModel>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QtQuick/QQuickItem>

#include "Presenters/BackupPresenter.h"

#include "../Data/DriveListItem.h"
#include "../Data/ThumbnailViewItem.h"

BackupView::BackupView(/*QWidget *parent,*/ IBackupPresenter* presenter) :
    //QWidget(parent),
    //_presenter(presenter),
    ui(new Ui::BackupView)
{
    ui->setupUi(this);

//    _folderTreeModel = std::make_shared<QFileSystemModel>();
//    QString rootPath = "C:\\Temp\\";//_driveListModel->index(0).data().toString();
//    _folderTreeModel->setRootPath(QDir::currentPath());
//    _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

    SetupDriveView();
    SetupFolderView();
    SetupThumbnailView();

    //ui->folderTree->setModel(_folderTreeModel.get());
    //ui->folderTree->setRootIndex(_folderTreeModel->index("E:"));
}

BackupView::~BackupView()
{
    delete ui;
}

void BackupView::SetupDriveView()
{
    dataList = new QList<QObject*>();

    _qmlContext = ui->quickWidget_2->rootContext();
    _qmlContext->setContextProperty("listModel", QVariant::fromValue(*dataList));
    ui->quickWidget_2->setSource(QUrl("./Widgets/DriveList.qml"));

    QQuickItem * item =   ui->quickWidget_2->rootObject();
    connect(item, SIGNAL(itemSelectionChanged(int)), this, SLOT(CurrentDriveChanged(int)));
}

void BackupView::SetupFolderView()
{
    _folderTreeModel = std::make_shared<QFileSystemModel>();
    ui->folderTree->setModel(_folderTreeModel.get());
}

QQmlContext*  qmlContext2;
QList<QObject*>*  _fileList;
void BackupView::SetupThumbnailView()
{
    //_qmlContext = ui->quickWidget_2->rootContext();
    //_qmlContext->setContextProperty("listModel", QVariant::fromValue(*dataList));
    _fileList = new QList<QObject*>();
    qmlContext2 = ui->quickWidget->rootContext();
    qmlContext2->setContextProperty("fileList", QVariant::fromValue(*_fileList));

    ui->quickWidget->setSource(QUrl("./Widgets/ThumbnailView.qml"));
}

void BackupView::TransferButtonClicked()
{
    emit StartTransfer();
}

void BackupView::CurrentDriveChanged(int currentDrive)
{
    emit DriveSelectionChanged(currentDrive);
}

void BackupView::SetDriveList(std::vector<DriveInfo> driveList)
{
    dataList->clear();

    for(auto& drive : driveList)
    {
        dataList->append(new DriveListItem(QString::fromStdString(drive.DriveName), QString::fromStdString(drive.DrivePath), drive.UsedSpace, drive.TotalSpace, QString::fromStdString(drive.SpaceUnit)));
    }

    _qmlContext->setContextProperty("listModel", QVariant::fromValue(*dataList));
}

void BackupView::SetItemList(std::vector<std::string> fileList)
{
     //qmlContext->setContextProperty("listModel", QVariant::fromValue(_fileList));
    _fileList->clear();
    for(auto& file : fileList)
    {
        _fileList->append(new ThumbnailViewItem("Test1", "Test2", 640, 480, 30));
    }

    qmlContext2->setContextProperty("fileList", QVariant::fromValue(*_fileList));
}

void BackupView::SetCurrentFolder(std::string folderPath)
{
    QString rootPath = QString::fromStdString(folderPath);

    if(folderPath == "")
    {
        ui->folderTree->setModel(nullptr);
        return;
    }

    ui->folderTree->setModel(_folderTreeModel.get());
    _folderTreeModel->setRootPath(QDir::currentPath());
    _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

    ui->folderTree->setRootIndex(_folderTreeModel->index(rootPath));
}
