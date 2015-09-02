#include "BackupView.h"
#include "ui_BackupView.h"

#include <QStringListModel>
#include <QFileSystemModel>
#include <QHeaderView>

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
    _driveListModel = new QStringListModel();
    ui->driveList->setModel(_driveListModel);

    _tableModel = new QStandardItemModel();
    ui->tableView->setModel(_tableModel);

    _tableModel->insertColumn(0);
    _tableModel->insertColumn(1);

    _tableModel->setHorizontalHeaderItem(0, new QStandardItem("Drive"));
    _tableModel->setHorizontalHeaderItem(1, new QStandardItem("Used/Avaialble"));

    QHeaderView* header = ui->tableView->horizontalHeader();
    header->setSectionsClickable(false);

    QItemSelectionModel* selectionModel = ui->driveList->selectionModel();
    connect(selectionModel, SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(CurrentDriveChanged(const QModelIndex&, const QModelIndex&)));
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

void BackupView::SetDriveList(std::vector<std::string> driveList)
{
    QStringList stringList;
    int i = 0;

    _tableModel->removeRows(0, _tableModel->rowCount());
    for(std::string drive : driveList)
    {
        stringList.push_back(QString::fromStdString(drive));

        _tableModel->insertRow(i, new QStandardItem(QString::fromStdString(drive)));
        i++;
    }
       //stringList.push_back("C:");

    _driveListModel->setStringList(stringList);
    _driveListModel->index(0);
    ui->driveList->setCurrentIndex(_driveListModel->index(0, 0));


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
