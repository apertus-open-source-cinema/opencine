#include "BackupLayout.h"
#include "ui_BackupLayout.h"

#include <QFileDialog>
#include <QGraphicsBlurEffect>
#include <QPainter>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

#include <QPdfWriter>

#include <QtPrintSupport/QPrinter>

class GridDelegate : public QStyledItemDelegate
{
public:
    explicit GridDelegate(QObject * parent = 0) : QStyledItemDelegate(parent) { }

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
    {
        painter->save();
        painter->setPen(QColor("#FA8756"));
        painter->drawRect(option.rect);
        painter->restore();

        QStyledItemDelegate::paint(painter, option, index);
    }
};

BackupLayout::BackupLayout(QWidget *parent, const BackupPresenter& backupPresenter) :
    QWidget(parent),
    _presenter(&const_cast<BackupPresenter&>(backupPresenter)),
    ui(new Ui::BackupLayout)
{
    ui->setupUi(this);

    _qmlContext = ui->quickWidget->rootContext();
    ui->quickWidget->engine()->addImageProvider(QString("thumbnail"), new ThumbnailProvider());

    _qmlContext->setContextProperty("fileList", QVariant::fromValue(_fileList));

    ui->quickWidget->setSource(QUrl("./Widgets/ThumbnailView.qml"));

    QStandardItemModel* model2 = new QStandardItemModel();
    model2->setRowCount(15);
    model2->setColumnCount(2);

    for(int r = 0; r < model2->rowCount(); r++)
    {
        for(int c = 0; c < model2->columnCount(); c++)
        {
            if(c == 0)
            {
                model2->setItem(r, c, new QStandardItem("Property"));
            }
            else
            {
                model2->setItem(r, c, new QStandardItem("Value"));
            }
        }
    }

    model2->setHorizontalHeaderItem(0, new QStandardItem("Property"));
    model2->setHorizontalHeaderItem(1, new QStandardItem("Value"));

    ui->treeView_2->setItemDelegate(new GridDelegate());
    ui->treeView_2->setModel(model2);

    ui->driveList->setModel(_presenter->GetDriveListModel());
    ui->driveList->setCurrentIndex(ui->driveList->model()->index(0,0));

    ui->folderTree->setModel(_presenter->GetFolderTreeModel());
    ui->folderTree->setRootIndex(_presenter->GetFolderTreeModel()->setRootPath("/media/andi/TOSHIBA EXT"));

    //Disable type and size column
    ui->folderTree->setColumnHidden(1, true);
    ui->folderTree->setColumnHidden(2, true);

    connect(ui->driveList->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), _presenter, SLOT(CurrentDriveChanged(QModelIndex, QModelIndex)));
    connect(ui->folderTree->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), _presenter, SLOT(CurrentFolderChanged(QItemSelection, QItemSelection)));

    connect(_presenter, SIGNAL(DriveSelectionChanged(QModelIndex)), SLOT(DriveSelectionChanged(QModelIndex)));
    connect(_presenter, SIGNAL(FolderChanged(std::vector<FileInfo*>)), SLOT(FolderSelectionChanged(std::vector<FileInfo*>)));
}

BackupLayout::~BackupLayout()
{
    delete ui;
}

void BackupLayout::DriveSelectionChanged(QModelIndex driveRoot)
{
    ui->folderTree->setRootIndex(driveRoot);
}

void BackupLayout::FolderSelectionChanged(std::vector<FileInfo*> fileList)
{
    _fileList.clear();

    for(auto& fileInfo : fileList)
    {
        _fileList.push_back(fileInfo);
    }

    _qmlContext->setContextProperty("fileList", QVariant::fromValue(_fileList));
}

void BackupLayout::DriveListChanged()
{
    int i = 0;
}


QImage ThumbnailProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    //    dataStorage = new StaticMemoryAllocator();
    //    if(dataProvider.LoadFile(dataStorage, id.toStdString()))
    //    {
    //        image = QImage(dataStorage->GetFrame(0)->GetWidth(),dataStorage->GetFrame(0)->GetHeight(), QImage::Format_RGB16);
    //        image.fromData(QByteArray::fromRawData((const char*)dataStorage->GetFrame(0)->GetData(), dataStorage->GetFrame(0)->GetSize()));
    //        image = image.scaled(64, 32);
    //    }
    if(!image.load(id))
    {
        image.load("./Widgets/thumbnail_placeholder.png");
    }

    return image;
}

void BackupLayout::on_pushButton_3_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    int result = dialog.exec();
    if(result)
    {
        QString directory = dialog.selectedFiles().at(0);
        ui->comboBox->setCurrentText(directory);
        _presenter->SetMasterPath(directory);
    }
}

void BackupLayout::on_pushButton_clicked()
{
    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect();
    effect->setBlurRadius(5);

    this->setGraphicsEffect(effect);
    _presenter->TransferData();

    effect->setBlurRadius(0);
}
