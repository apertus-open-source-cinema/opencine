#include "BackupView.h"
#include "ui_BackupView.h"

#include <QStringListModel>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QtQuick/QQuickItem>
#include <QDebug>
#include <QtQml/QQmlEngine>

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
	dataList = new QList<QObject*>();

	_qmlContext = ui->driveListControl->rootContext();
	_qmlContext->setContextProperty("listModel", QVariant::fromValue(*dataList));

	//ui->driveListControl->setAttribute(Qt::WA_NoSystemBackground);

	//    _driveListDelegate = std::make_shared<QQmlComponent>(ui->driveListControl->engine(), QUrl::fromLocalFile("Widgets/DriveItem.qml"));

	//    if(_driveListDelegate != nullptr)
	//    {
	//        _qmlContext->setContextProperty("listDelegate", QVariant::fromValue(_driveListDelegate.get()));

	//        if(_driveListDelegate->isError())
	//        {
	//            qDebug() << "Error: " <<_driveListDelegate->errorString();
	//        }

	//        //        if( _driveListDelegate->status != QQmlComponent::Status::Ready )
	//        //        {
	//        //            if( _driveListDelegate->status == QQmlComponent::Error )
	//        //            {
	//        //                qDebug() << "Error: " <<_driveListDelegate->errorString();
	//        //            }
	//        //            return; // or maybe throw
	//        //        }

	//        _driveListDelegate->create(_qmlContext);
	//        ui->driveListControl->engine()->setObjectOwnership(_driveListDelegate.get(), QQmlEngine::CppOwnership);

	//    }

	ui->driveListControl->setSource(QUrl("./Widgets/DriveList.qml"));

	QQuickItem * item = ui->driveListControl->rootObject();
	connect(item, SIGNAL(itemSelectionChanged(int)), this, SLOT(CurrentDriveChanged(int)));
}

void BackupView::SetupFolderView()
{
	_folderTreeModel = std::make_shared<QFileSystemModel>();
	ui->folderTreeControl->setModel(_folderTreeModel.get());

	connect(ui->folderTreeControl->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(CurrentFolderChanged(const QItemSelection&, const QItemSelection&)));
}

QQmlContext*  qmlContext2;
//QList<QObject*>*  _fileList;
void BackupView::SetupThumbnailView()
{
	QQmlEngine *engine = ui->thumbnailViewControl->engine();
	engine->addImageProvider(QLatin1String("colors"), new QMLThumbnailProvider());

	_fileList = new QList<QObject*>();
	qmlContext2 = ui->thumbnailViewControl->rootContext();
	qmlContext2->setContextProperty("fileList", QVariant::fromValue(*_fileList));

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

void BackupView::SetDriveList(std::vector<DriveInfo> driveList)
{
	dataList->clear();

	for (auto& drive : driveList)
	{
		dataList->append(new DriveListItem(QString::fromStdString(drive.DriveName), QString::fromStdString(drive.DrivePath), drive.UsedSpace, drive.TotalSpace, QString::fromStdString(drive.SpaceUnit)));
	}

	_qmlContext->setContextProperty("listModel", QVariant::fromValue(*dataList));
}

void BackupView::SetItemList(std::vector<QString> fileList)
{
	_fileList->clear();

	for (auto& file : fileList)
	{
		_fileList->append(new ThumbnailViewItem(file, file, 640, 480, 30));
		//_fileList->append(new ThumbnailViewItem("Test1", "Test2", 640, 480, 30));
	}

	qmlContext2->setContextProperty("fileList", QVariant::fromValue(*_fileList));
}

void BackupView::SetDestinationList(std::vector<QString> destinationList)
{
	ui->destinationsControl->SetDestinationList(destinationList);
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