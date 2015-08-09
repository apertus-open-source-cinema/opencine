#include "BackupView.h"
#include "ui_BackupView.h"

#include <QStringListModel>
#include <QFileSystemModel>

#include "Presenters/BackupPresenter.h"

BackupView::BackupView(/*QWidget *parent,*/ IBackupPresenter* presenter) :
    //QWidget(parent),
    //_presenter(presenter),
    ui(new Ui::BackupView)
{
    ui->setupUi(this);

    _qmlContext = ui->quickWidget->rootContext();
    //ui->quickWidget->engine()->addImageProvider(QString("thumbnail"), new ThumbnailProvider());

    //_qmlContext->setContextProperty("fileList", QVariant::fromValue(_fileList));

    ui->quickWidget->setSource(QUrl("./Widgets/ThumbnailView.qml"));


    /*    QFileSystemModel* _folderTreeModel = new QFileSystemModel();
    QString rootPath = _driveListModel->index(0).data().toString();
    _folderTreeModel->setRootPath(rootPath);
    _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs)*/;

    //SetupDriveView();
    //SetupFolderView();
}

BackupView::~BackupView()
{
    delete ui;
}

//void BackupView::SetupDriveView()
//{
//    connect(_presenter, SIGNAL(DriveListChanged(std::vector<std::string>)), this, SLOT(DriveListChanged(std::vector<std::string>)));
//    _presenter->RefreshDriveList();
//    connect(ui->driveList->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(SelectDrive(const QModelIndex&, const QModelIndex&)));
//}

//void BackupView::SetupFolderView()
//{
//    connect(_presenter, SIGNAL(DriveSelectionChanged(QModelIndex)), SLOT(DriveSelectionChanged(QModelIndex)));
//}

//void BackupView::DriveListChanged(std::vector<std::string> driveList)
//{
//    QStringList stringList;
//    for(std::string drive : driveList)
//    {
//        stringList.push_back(QString::fromStdString(drive));
//    }

//    QStringListModel* _driveListModel = new QStringListModel();
//    _driveListModel->setStringList(stringList);

//    ui->driveList->setModel(_driveListModel);
//}

//void BackupView::SelectDrive(const QModelIndex& current, const QModelIndex& previous)
//{
//    _presenter->SelectDrive(current.data().toString().toStdString());
//}


void BackupView::TransferButtonClicked()
{
    emit StartTransfer();
}

void BackupView::SetDriveList(std::vector<std::string> driveList)
{
    QStringList stringList;
    for(std::string drive : driveList)
    {
        stringList.push_back(QString::fromStdString(drive));
    }

    QStringListModel* _driveListModel = new QStringListModel();
    _driveListModel->setStringList(stringList);

    ui->driveList->setModel(_driveListModel);
}
