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

    //std::vector<FileInfo*> fileList = _presenter->GetFileList();
    //_fileList.append(fileList.at(0));
    //    //_qmlContext->setContextProperty("fileList", QVariant::fromValue(list));

    _qmlContext = ui->quickWidget->rootContext();
    ui->quickWidget->engine()->addImageProvider(QString("thumbnail"), new ThumbnailProvider());

    _qmlContext->setContextProperty("fileList", QVariant::fromValue(_fileList));

    ui->quickWidget->setSource(QUrl("./Widgets/ThumbnailView.qml"));

    //    list.append(fileList.at(0));
    //    list.append(fileList.at(0));
    //    list.append(fileList.at(0));
    //    _qmlContext->setContextProperty("fileList", QVariant::fromValue(list));

    //_qmlContext->setContextProperty("fileList", QVariant::fromValue(list));
    //QFileSystemModel* model = new QFileSystemModel();
    //model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::AllDirs);
    //model->setSorting(QDir::Name | QDir::IgnoreCase);

    /*ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(QDir::rootPath()));
    ui->treeView->setWindowTitle(QObject::tr("Dir View:")+QDir::homePath());
    */
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

    //ui->treeView_3->setRootIndex(model3->index("/media/andi/TOSHIBA EXT"));

    //model3->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

    ui->driveList->setModel(_presenter->GetDriveListModel());
    ui->driveList->setCurrentIndex(ui->driveList->model()->index(0,0));

    ui->folderTree->setModel(_presenter->GetFolderTreeModel());
    ui->folderTree->setRootIndex(_presenter->GetFolderTreeModel()->setRootPath("/media/andi/TOSHIBA EXT"));

    //Disable type and size column
    ui->folderTree->setColumnHidden(1, true);
    ui->folderTree->setColumnHidden(2, true);

    //ui->folderTree->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    connect(ui->driveList->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), _presenter, SLOT(CurrentDriveChanged(QModelIndex, QModelIndex)));
    connect(ui->folderTree->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), _presenter, SLOT(CurrentFolderChanged(QItemSelection, QItemSelection)));

    //connect(ui->driveList->selectionModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(DriveListChanged()));

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
    QImage image = ui->quickWidget->grabFramebuffer();
    //QPdfWriter pdfWriter("test.pdf");
    //pdfWriter.setResolution(96);
    //pdfWriter.setPageSize(QPagedPaintDevice::A4);

    //double xscale = (double)pdfWriter.width()/(double)image.width();
    //double yscale = (double)pdfWriter.height()/(double)image.height();
    //double scale = qMin(xscale, yscale);
    //painter.translate(pdfWriter.paperRect().x() + pdfWriter.pageRect().width()/2,
    //                  pdfWriter.paperRect().y() + pdfWriter.pageRect().height()/2);
    //painter.scale(scale, scale);
    //painter.translate(-width()/2, -height()/2);
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("test.pdf");
    QPainter painter(&printer); //ui->quickWidget->render(&pdfWriter);
    painter.drawImage(0,0, image);
    painter.end();


    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect();
    effect->setBlurRadius(5);

    this->setGraphicsEffect(effect);
    _presenter->TransferData();

    effect->setBlurRadius(0);
}
