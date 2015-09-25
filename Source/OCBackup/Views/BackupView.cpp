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

  //    _folderTreeControlModel = std::make_shared<QFileSystemModel>();
  //    QString rootPath = "C:\\Temp\\";//_driveListModel->index(0).data().toString();
  //    _folderTreeControlModel->setRootPath(QDir::currentPath());
  //    _folderTreeControlModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

  SetupDriveView();
  SetupFolderView();
  SetupThumbnailView();

  //ui->folderTreeControl->setModel(_folderTreeControlModel.get());
  //ui->folderTreeControl->setRootIndex(_folderTreeControlModel->index("E:"));
}

BackupView::~BackupView()
{
  delete ui;
}

void BackupView::SetupDriveView()
{
  dataList = new QList<QObject*>();

  _qmlContext = ui->driveListControl->rootContext();
  _qmlContext->setContextProperty("listModel", QVariant::fromValue(*dataList));
  ui->driveListControl->setSource(QUrl("./Widgets/DriveList.qml"));

  QQuickItem * item =   ui->driveListControl->rootObject();
  connect(item, SIGNAL(itemSelectionChanged(int)), this, SLOT(CurrentDriveChanged(int)));
}

void BackupView::SetupFolderView()
{
  _folderTreeModel = std::make_shared<QFileSystemModel>();
  ui->folderTreeControl->setModel(_folderTreeModel.get());
}

QQmlContext*  qmlContext2;
QList<QObject*>*  _fileList;
void BackupView::SetupThumbnailView()
{
  _fileList = new QList<QObject*>();
  qmlContext2 = ui->thumbnailViewControl->rootContext();
  qmlContext2->setContextProperty("fileList", QVariant::fromValue(*_fileList));

  ui->thumbnailViewControl->setSource(QUrl("./Widgets/ThumbnailView.qml"));
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
      ui->folderTreeControl->setModel(nullptr);
      return;
    }

  ui->folderTreeControl->setModel(_folderTreeModel.get());
  _folderTreeModel->setRootPath(QDir::currentPath());
  _folderTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);

  ui->folderTreeControl->setRootIndex(_folderTreeModel->index(rootPath));
}
