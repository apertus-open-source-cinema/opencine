#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QItemDelegate>
#include <QStandardItemModel>
#include <QPainter>
#include <QFileDialog>
#include <QTimer>

#include "API/IDataProvider.h"

#include "MediaExplorerView.h"
#include "PreviewPane.h"
#include "TestPluginA.h"

#include <dirent.h>

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

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(new PreviewPane(nullptr));
    ui->tab_4->setLayout(gridLayout);

    ui->dockWidget_3->setWidget(new MediaExplorerView(new MediaExplorerPresenter()));

    /*QMenu* importMenu = new QMenu();
    QAction* testAction = new QAction("test menu item", this);
    connect(testAction,SIGNAL(triggered()),this, SLOT(SelectImportFolder()));
    importMenu->addAction(testAction);*/
}

/*int currentImageIndex = 0;
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
}*/

MainWindow::~MainWindow()
{
    //imageProcessor->recycle();
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    //ui->previewArea->fitInView(it, Qt::KeepAspectRatio);
}

/*void MainWindow::SelectImportFolder()
{
    //QFileDialog* dialog = new QFileDialog(this);
    //dialog->setFileMode(QFileDialog::Directory);
    //dialog->setOption(QFileDialog::ShowDirsOnly);
    //dialog->show();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    int i = 0;
}*/
