#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QItemDelegate>
#include <QStandardItemModel>
#include <QPainter>
#include <QFileDialog>
#include <QTimer>

#include "ClipInformationItem.h"

#include "API/IDataProvider.h"

#include "PreviewPane.h"
#include "TestPluginA.h"

#include <dirent.h>

class ClipInformationModel : public QAbstractListModel
{
public:
    ClipInformationModel(QObject * parent = 0);
    ~ClipInformationModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    std::vector<ClipInformationItem*> clipItemList;

    // QAbstractItemModel interface
public:
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
};

/*
  \class MyListModel
*/
ClipInformationModel::ClipInformationModel(QObject * parent)
    : QAbstractListModel(parent)
{
}

ClipInformationModel::~ClipInformationModel()
{
}

int ClipInformationModel::rowCount(const QModelIndex & parent) const
{
    return 35;
}

QVariant ClipInformationModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        const QString s = QString("Clip %1").arg(index.row());
        return s;
    }

    return QVariant();
}

bool ClipInformationModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    endInsertRows();
    return true;
}

bool ClipInformationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    clipItemList.push_back((ClipInformationItem*)value.data());
    return true;
}

/*
  \class MyCustomListViewItem
*/
class MyCustomListViewItemDelegate : public QItemDelegate
{
public:
    MyCustomListViewItemDelegate(QObject * parent = 0);
    ~MyCustomListViewItemDelegate();
    virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

protected:
    ClipInformationItem* _itemWidget;
};

/*
  \class MyCustomListViewItemDelegate
*/
MyCustomListViewItemDelegate::MyCustomListViewItemDelegate(QObject * parent)
    : QItemDelegate(parent)
    ,_itemWidget(new ClipInformationItem())
{
}

MyCustomListViewItemDelegate::~MyCustomListViewItemDelegate()
{
    if (_itemWidget)
    {
        delete _itemWidget;
        _itemWidget = NULL;
    }
}

void MyCustomListViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    _itemWidget->resize(option.rect.size());

    // Update data of widget here.
    const QString s = index.data().toString();
    const QString s2 = QString("In detail it means %1").arg(s);
    _itemWidget->SetFilename(s.toStdString());
    //_itemWidget->_ui.labelDescription->setText(s2);
    //_itemWidget->_ui.progressBar->setValue( index.row() * 2 );

    // Change the background color of the widget if it is selected.
    QPalette pal;
    if ((option.state & QStyle::State_Selected) == QStyle::State_Selected)
    {
        pal.setBrush(QPalette::Window, QBrush(QColor(Qt::lightGray)));
    }
    else
    {
        pal.setBrush(QPalette::Window, QBrush(QColor(Qt::transparent)));
    }
    _itemWidget->setPalette(pal);

    // Paint the widget now.
    painter->save();
    painter->translate(option.rect.topLeft());
    _itemWidget->render(painter);
    painter->restore();
}

QSize MyCustomListViewItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    const int width = _itemWidget->minimumWidth();
    const int height = _itemWidget->height();
    return QSize(width, height);
}

struct PreviewImageStruct
{
    int width;
    int height;

    unsigned int dataSize;
    unsigned char* dataPtr;
};

std::vector<std::string> files;
std::vector<PreviewImageStruct*> memoryImages;

QGraphicsScene* scene;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create test data
    //QStringListModel* model = new QStringListModel(this);
    //QStringList clipList;
    //clipList << "Clip 1" << "Clip 2" << "Clip 3";
    //model->setStringList(clipList);

    ClipInformationModel* model = new ClipInformationModel(this);
    ClipInformationItem* widget = new ClipInformationItem();
    ClipInformationItem* widget2 = new ClipInformationItem();

    //QApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);


    //ui->listView->setItemDelegate(new MyCustomListViewItemDelegate());

//    imageProcessor = new LibRaw();

//    std::string dir = "./Images1";
//    DIR *dp;
//    struct dirent *dirp;
//    if((dp  = opendir(dir.c_str())) == NULL) {
//        //std::cout << "Error(" << errno << ") opening " << dir << std::endl;
//        int i = 0;
//    }

//    while ((dirp = readdir(dp)) != NULL)
//    {
//        files.push_back(std::string("./Images1/") + std::string(dirp->d_name));
//    }
//    closedir(dp);

//    std::sort(files.begin(), files.end());

//    files.erase(files.begin());
//    files.erase(files.begin());

//    imageProcessor->open_file("03000253.DNG");

//    // Let us unpack the image
//    imageProcessor->unpack();

//    // Convert from imgdata.rawdata to imgdata.image:
//    imageProcessor->raw2image();

//    int error = 0;
//    int status = imageProcessor->dcraw_process();
//    libraw_processed_image_t* tempImg = imageProcessor->dcraw_make_mem_image(&error);
//    //imageProcessor->dcraw_ppm_tiff_writer("test456.ppm");

//    QImage* previewImage = new QImage((int)tempImg->width, (int)tempImg->height, QImage::Format_RGB888);
//    for (unsigned int y = 0; y < previewImage->height(); y++)
//    {
//        memcpy(previewImage->scanLine(y), &tempImg->data[y * previewImage->bytesPerLine()], previewImage->bytesPerLine());
//    }

//    //QByteArray array = QByteArray::fromRawData((const char*)tempImg->data, tempImg->data_size);

//    // Finally, let us free the image processor for work with the next image

//    scene = new QGraphicsScene();
//    it = new QGraphicsPixmapItem(QPixmap::fromImage(*previewImage));
//    scene->addItem(it);
//    //scene->addPixmap(QPixmap::fromImage(*previewImage));
//    ui->previewArea->setScene(scene);

//    imageProcessor->recycle();

//    imageProcessor = new LibRaw();
//    for(unsigned int i = 0; i < files.size(); ++i)
//    {
//        imageProcessor->open_file(files.at(i).c_str());

//        // Let us unpack the image
//        imageProcessor->unpack();

//        // Convert from imgdata.rawdata to imgdata.image:
//        imageProcessor->raw2image();

//        int error = 0;
//        int status = imageProcessor->dcraw_process();
//        libraw_processed_image_t* tempImg = imageProcessor->dcraw_make_mem_image(&error);

//        PreviewImageStruct* pis = new PreviewImageStruct();
//        pis->width = tempImg->width;
//        pis->height = tempImg->height;

//        pis->dataPtr = new unsigned char[tempImg->data_size];
//        memcpy(pis->dataPtr, tempImg->data, tempImg->data_size);

//        memoryImages.push_back(pis);
//        //imageProcessor->free_image();
//        imageProcessor->dcraw_clear_mem(tempImg);
//    }

//    imageProcessor->recycle();

    //ui->graphicsView->setSceneRect(0,0,ui->graphicsView->frameSize().width(),ui->graphicsView->frameSize().height());
    //ui->graphicsView->show();
    //model->insertRows(0, 0, QModelIndex());
    //QModelIndex index = model->index(0, 0, QModelIndex());
    //model->setData(index, widget);
    //

    //model->appendRow(widget2);

    //    model->insertRows(5, 7, QModelIndex());

    //        for (int row = 5; row < 12; ++row) {
    //            QModelIndex index = model->index(row, 0, QModelIndex());
    //            model->setData(index, QString::number(row+1));
    //        }

    //TestPluginA* testPlugin = new TestPluginA();

    QMenu* importMenu = new QMenu();
    QAction* testAction = new QAction("test menu item", this);
    connect(testAction,SIGNAL(triggered()),this, SLOT(SelectImportFolder()));
    importMenu->addAction(testAction);

    PreviewPane* pp = new PreviewPane();
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(pp);

    ui->page_2->setLayout(gridLayout);
    //ui->toolButton->setMenu(importMenu);

    //ui->listView->setModel(model);

    //QTimer* timer = new QTimer();
    //connect(timer, SIGNAL(timeout()), this, SLOT(PlayImages()));
    //timer->start(1000/24);

    //PlayImages(files);
}

int currentImageIndex = 0;
QImage* previewImage;
bool rrr = false;

void MainWindow::PlayImages()
{
    PreviewImageStruct* im = memoryImages.at(currentImageIndex);

    if(!rrr)
    {
        previewImage = new QImage((int)im->width, (int)im->height, QImage::Format_RGB888);
        rrr = true;
    }

    //imageProcessor->dcraw_ppm_tiff_writer("test456.ppm");

    for (unsigned int y = 0; y < previewImage->height(); y++)
    {
        memcpy(previewImage->scanLine(y), &im->dataPtr[y * previewImage->bytesPerLine()], previewImage->bytesPerLine());
    }

    it->setPixmap(QPixmap::fromImage(*previewImage));
    //scene->clear();
    //scene->addPixmap(QPixmap::fromImage(*previewImage));
    //scene->addItem(it);

    //scene->invalidate();

    currentImageIndex++;
    if(currentImageIndex == files.size())
    {
        currentImageIndex = 0;
    }

    ui->frameCount->setText(QString::number(currentImageIndex));

    //imageProcessor->recycle();
}

MainWindow::~MainWindow()
{
    //imageProcessor->recycle();
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    //ui->previewArea->fitInView(it, Qt::KeepAspectRatio);
}

void MainWindow::SelectImportFolder()
{
    //QFileDialog* dialog = new QFileDialog(this);
    //dialog->setFileMode(QFileDialog::Directory);
    //dialog->setOption(QFileDialog::ShowDirsOnly);
    //dialog->show();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    int i = 0;
}
