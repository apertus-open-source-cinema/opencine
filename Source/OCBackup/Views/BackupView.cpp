#include "BackupView.h"
#include "ui_BackupView.h"

#include <QStringListModel>
#include <QFileSystemModel>
#include <QHeaderView>

#include "Presenters/BackupPresenter.h"

#include "../Data/DriveListItem.h"

BackupView::BackupView(/*QWidget *parent,*/ IBackupPresenter* presenter) :
    //QWidget(parent),
    //_presenter(presenter),
    ui(new Ui::BackupView)
{
    ui->setupUi(this);

    //_qmlContext = ui->quickWidget->rootContext();
    //ui->quickWidget->setSource(QUrl("./Widgets/ThumbnailView.qml"));

    dataList = new QList<QObject*>();

    _qmlContext = ui->quickWidget_2->rootContext();
    ui->quickWidget_2->setSource(QUrl("./Widgets/DriveList.qml"));
    _qmlContext->setContextProperty("listModel", QVariant::fromValue(*dataList));

    //ui->quickWidget->engine()->addImageProvider(QString("thumbnail"), new ThumbnailProvider());

    //_qmlContext->setContextProperty("fileList", QVariant::fromValue(_fileList));

    QFileSystemModel* _folderTreeModel = new QFileSystemModel();
    QString rootPath = "C:\\Temp\\";//_driveListModel->index(0).data().toString();
    _folderTreeModel->setRootPath(QDir::currentPath());
    _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);


    SetupDriveView();
    SetupFolderView();

    ui->folderTree->setModel(_folderTreeModel);
    ui->folderTree->setRootIndex(_folderTreeModel->index("E:"));
}

BackupView::~BackupView()
{
    delete ui;
}

void BackupView::SetupDriveView()
{
//    _driveListModel = new QStringListModel();
//    ui->driveList->setModel(_driveListModel);

//    QItemSelectionModel* selectionModel = ui->driveList->selectionModel();
//    connect(selectionModel, SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(CurrentDriveChanged(const QModelIndex&, const QModelIndex&)));
}

void BackupView::SetupFolderView()
{
    //    connect(_presenter, SIGNAL(DriveSelectionChanged(QModelIndex)), SLOT(DriveSelectionChanged(QModelIndex)));
    _folderTreeModel = new QFileSystemModel();
    ui->folderTree->setModel(_folderTreeModel);
}

void BackupView::TransferButtonClicked()
{
    emit StartTransfer();
}

void BackupView::CurrentDriveChanged(const QModelIndex& current, const QModelIndex &previous)
{
    emit DriveSelectionChanged(current.row());
}

void BackupView::SetDriveList(std::vector<DriveInfo> driveList)
{
    dataList->clear();

    for(auto& drive : driveList)
    {
        //stringList.push_back(QString::fromStdString(drive));
        dataList->append(new DriveListItem(QString::fromStdString(drive.DriveName), QString::fromStdString(drive.DrivePath), drive.UsedSpace, drive.TotalSpace, QString::fromStdString(drive.SpaceUnit)));

        //i++;
    }

    _qmlContext->setContextProperty("listModel", QVariant::fromValue(*dataList));

    //    _driveListModel->setStringList(stringList);
    //    _driveListModel->index(0);
    //    ui->driveList->setCurrentIndex(_driveListModel->index(0, 0));
}

void BackupView::SetCurrentFolder(std::string folderPath)
{
    QString rootPath = QString::fromStdString(folderPath);//_driveListModel->index(0).data().toString();

    if(folderPath == "")
    {
        ui->folderTree->setModel(nullptr);
        return;
    }

    ui->folderTree->setModel(_folderTreeModel);
    _folderTreeModel->setRootPath(QDir::currentPath());
    _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

    ui->folderTree->setRootIndex(_folderTreeModel->index(rootPath));
}
