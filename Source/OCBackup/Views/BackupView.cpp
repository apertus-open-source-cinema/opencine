#include "BackupView.h"
#include "ui_BackupView.h"

#include <QFileSystemModel>
#include <QtQuick/QQuickItem>
#include <QDebug>

#include "Presenters/BackupPresenter.h"

#include <Helper/QMLThumbnailProvider.h>

#include "../Data/DriveListItem.h"
#include "../Data/ThumbnailViewItem.h"

BackupView::BackupView(/*QWidget *parent,*/ IBackupPresenter* presenter) :
    //QWidget(parent),
    //_presenter(presenter),
    ui(new Ui::BackupView)
{
    ui->setupUi(this);

    //    _folderTreeControlModel = std::make_shared<QFileSystemModel>();
    //    QString rootPath = "C:\\Temp\\";//_driveListModel->index(0).data().toString();
    //    _folderTreeControlModel->setRootPath(QDir::currentPath());
    //    _folderTreeControlModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

    SetupDriveView();
    SetupFolderView();
    SetupThumbnailView();
    SetupDestinationsView();

    connect(ui->destinationsControl, SIGNAL(AddDestinationClicked()), this, SIGNAL(AddDestinationClicked()));
    //ui->folderTreeControl->setModel(_folderTreeControlModel.get());
    //ui->folderTreeControl->setRootIndex(_folderTreeControlModel->index("E:"));
}

BackupView::~BackupView()
{
    delete ui;
}

void BackupView::SetupDriveView()
{
    //dataList = new QList<QObject*>();

    _qmlContext = ui->driveListControl->rootContext();
    _qmlContext->setContextProperty("listModel", QVariant::fromValue(dataList));

    ui->driveListControl->setSource(QUrl("./Widgets/DriveList.qml"));

    QQuickItem* item = ui->driveListControl->rootObject();
    connect(item, SIGNAL(itemSelectionChanged(int)), this, SLOT(CurrentDriveChanged(int)));
}

void BackupView::SetupFolderView()
{
    _folderTreeModel = std::make_shared<QFileSystemModel>();
    ui->folderTreeControl->setModel(_folderTreeModel.get());

    connect(ui->folderTreeControl->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(CurrentFolderChanged(const QItemSelection&, const QItemSelection&)));
}

//QList<QObject*>*  _fileList;
void BackupView::SetupThumbnailView()
{
    QQmlEngine *engine = ui->thumbnailViewControl->engine();
    engine->addImageProvider(QLatin1String("OCthumb"), new QMLThumbnailProvider());

    _fileList = new QList<QObject*>();
    _qmlContext = ui->thumbnailViewControl->rootContext();
    _qmlContext->setContextProperty("fileList", QVariant::fromValue(*_fileList));

    ui->thumbnailViewControl->setSource(QUrl("./Widgets/ThumbnailView.qml"));
}

void BackupView::SetupDestinationsView()
{
    //_fileList = new QList<QObject*>();
    //qmlContext2 = ui->thumbnailViewControl->rootContext();
    //qmlContext2->setContextProperty("fileList", QVariant::fromValue(*_fileList));
}

void BackupView::TransferButtonClicked()
{
    //TODO: Rework create a task directly, later it can be pushed through an event bus
    emit StartTransfer();
}

void BackupView::CurrentDriveChanged(int currentDrive)
{
    emit DriveSelectionChanged(currentDrive);
}

void BackupView::CurrentFolderChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    QModelIndex itemIndex = ui->folderTreeControl->selectionModel()->currentIndex();
    QString path = _folderTreeModel->filePath(itemIndex);

    emit FolderSelectionChanged(path);
}

void BackupView::SetDriveList(std::vector<PathInfo> driveList)
{
    dataList.clear();

    for (auto& drive : driveList)
    {
        dataList.append(new DriveListItem(QString::fromStdString(drive.DriveName), QString::fromStdString(drive.DrivePath), drive.UsedSpace, drive.TotalSpace, QString::fromStdString(drive.SpaceUnit)));
    }

    _qmlContext = ui->driveListControl->rootContext();
    _qmlContext->setContextProperty("listModel", QVariant::fromValue(dataList));
}

void BackupView::SetItemList(std::vector<FileInfo> fileList)
{
    _fileList->clear();

    for (auto& fileInfo : fileList)
    {
        // TODO: supply path as first parameter, so it and file name are distinct values
        _fileList->append(new ThumbnailViewItem(fileInfo.GetFolderPath(), fileInfo.GetFileName(), 640, 480, 30));
    }

    _qmlContext = ui->thumbnailViewControl->rootContext();
    _qmlContext->setContextProperty("fileList", QVariant::fromValue(*_fileList));
}

void BackupView::SetDestinationList(std::vector<PathInfo> destinationList)
{
    _destinationList.clear();

    for (auto& destination : destinationList)
    {
        // TODO: supply path as first parameter, so it and file name are distinct values
        _destinationList.push_back(new DestinationsListItem(QString::fromStdString(destination.DriveName), QString::fromStdString(destination.DrivePath), 640, 480, "30"));
    }

    ui->destinationsControl->SetDestinationList(_destinationList);
}

void BackupView::SetCurrentFolder(QString folderPath)
{
    if (folderPath == "")
    {
        ui->folderTreeControl->setModel(nullptr);
        return;
    }

    ui->folderTreeControl->setModel(_folderTreeModel.get());
    _folderTreeModel->setRootPath(QDir::currentPath());
    _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

    ui->folderTreeControl->setRootIndex(_folderTreeModel->index(folderPath));
}
