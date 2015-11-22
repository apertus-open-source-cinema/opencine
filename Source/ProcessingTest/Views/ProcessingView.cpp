#include "ProcessingView.h"
#include "ui_ProcessingView.h"

#include <thread>

#include <QFile>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QTime>
#include <QTimer>

#include "Controls/PreviewPane.h"

QByteArray imageData;
unsigned short* textureData;
unsigned short* textureDataRed;
unsigned short* textureDataGreen;
unsigned short* textureDataBlue;

unsigned short texPixels[4] = {
    32000, 0, 16000, 8000
};

QImage* img;

ProcessingView::ProcessingView(QWidget *parent) :
    ui(new Ui::ProcessingView)
{
    ui->setupUi(this);

    LoadTexture();

    img  = new QImage(4096, 3072, QImage::Format_RGB32);
    QRgb* pixels = reinterpret_cast<QRgb*>(img->bits());

    //    memcpy(pixels, imageData, 4096 * 3072);

    //    QTime myTimer;
    //    myTimer.start();

    //    //uchar* pixels2 = new uchar[4096 * 3072 * 2];
    int j = 0;
    int currentColor = 0;
    for (long long i=0;i < imageData.size(); i += 3)
    {
        uint16_t pixel1 = (imageData.constData()[i + 1] << 4) + ((imageData.constData()[i] & 0xF0) >> 4);
        pixel1 &= 0xFFF;

        uint16_t pixel2 = ((imageData.constData()[i + 2] & 0x0F) << 8) + imageData.constData()[i + 1];

        pixels[j] = qRgb(pixel1, pixel1, pixel1);        //pixels2[i] = pixel1;
        pixels[j + 1] = qRgb(pixel2, pixel2, pixel2);
        //pixels2[i + 1] = pixel2;

        //        currentColor = bayerMatrixRGGB[i / 4096 % 2][(i / 3072) % 2];
        //        if(currentColor == 0)
        //        {
        //            pixels[j] = qRgb(pixel1, 0, 0);
        //        }
        //        else if(currentColor == 1)
        //        {
        //            pixels[j] = qRgb(0, pixel1, 0);
        //        }
        //        else if(currentColor == 2)
        //        {
        //            pixels[j] = qRgb(0, 0, pixel1);
        //        }

        //        pixels[j + 1] = qRgb(0, pixel2, pixel2);
        //        currentColor = bayerMatrixRGGB[i / 4096 % 2 + 1][(i / 3072 + 1) % 2];
        //        if(currentColor == 0)
        //        {
        //            pixels[j + 1] = qRgb(pixel1, 0, 0);
        //        }
        //        else if(currentColor == 1)
        //        {
        //            pixels[j + 1] = qRgb(0, pixel1, 0);
        //        }
        //        else if(currentColor == 2)
        //        {
        //            pixels[j + 1] = qRgb(0, 0, pixel1);
        //        }

        j += 2;
    }
}

ProcessingView::~ProcessingView()
{
    delete ui;
}

char bayerMatrixRGGB[2][2] = {{0, 1},
                              {1, 2}};

void ProcessingView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect geo = this->geometry();

    int x, y, width, height;

    x = geo.x()+10;
    y = geo.y()+10;
    width = geo.width()-10;
    height = geo.height()-10;

    painter.fillRect(x, y, width, height, QColor(220,220,220));

    painter.drawText(x+10, y+10, "Machine " + QString::number(12345));


    //img->loadFromData((const char*)pixels2);
    //pixels = pixels2;
    //pixels[j] = qRgb(0, pixel1, 0);

    //    for(unsigned int y = 0; y < 3071; y++)
    //    {
    //        for(unsigned x = 0; x < 4095; x += 2)
    //        {
    //            uint16_t pixel1 = (imageData.constData()[(x * y + x) + 1] << 4) + ((imageData.constData()[(x * y + x)] & 0xF0) >> 4);
    //            pixel1 &= 0xFFF;

    //            uint16_t pixel2 = ((imageData.constData()[(x * y + x) + 2] & 0x0F) << 8) + imageData.constData()[(x * y + x) + 1];

    //            pixels[(x * y) + x] = qRgb(pixel1, pixel1, pixel1);
    //            pixels[(x * y) + x + 1] = qRgb(pixel2, pixel2, pixel2);

    //        }
    //    }

    //int nMilliseconds = myTimer.elapsed();

    //qDebug() << "Width = " << this->width();
    //qDebug() << "Height = " << this->height();

    //painter.scale(10.0, 10.0);
    painter.scale(0.3, 0.3);
    painter.drawImage(0, 0, *img);

    ui->openGLWidget->SetTextureRed(4096, 3072, textureDataRed);
    ui->openGLWidget->SetTextureGreen(4096, 3072, textureDataGreen);
    ui->openGLWidget->SetTextureBlue(4096, 3072, textureDataBlue);

    //ui->openGLWidget->SetTexture(2, 2, texPixels);
}

void task1(int value, int offset, int length)
{
    QTime timer;
    timer.start();

    for(int i = offset; i < offset + length; i++)
    {
        textureData[i] = value;
    }

    qDebug() << value << " elapsed: " <<  timer.elapsed();
}

void ProcessingView::LoadTexture()
{
    QFile file("axiom.raw12");
    if (!file.open(QIODevice::ReadOnly)) return;
    imageData = file.readAll();

    textureData = new unsigned short[4096 * 3072];

    //uchar* pixels2 = new uchar[4096 * 3072 * 2];
    int j = 0;
    int currentColor = 0;
    for (long long i=0;i < imageData.size(); i += 3)
    {
        uint16_t pixel1 = (imageData.constData()[i] << 4) + ((imageData.constData()[i + 1] & 0xF0) >> 4);
        pixel1 &= 0xFFF;

        uint16_t pixel2 = ((imageData.constData()[i + 1] & 0x0F) << 8) + imageData.constData()[i + 2];

        textureData[j] = pixel1;
        textureData[j + 1] = pixel2;

        j += 2;
    }

    QTime timer;
    timer.start();

    textureDataRed = new unsigned short[4096 * 3072];
    textureDataGreen = new unsigned short[4096 * 3072];
    textureDataBlue = new unsigned short[4096 * 3072];
    qDebug() << "Alllocate buffers: " <<  timer.elapsed();

    timer.restart();
    for(int rowIndex = 0; rowIndex < 3072; rowIndex += 2)
    {
        for(int columnIndex = 0; columnIndex < 4096; columnIndex++)
        {
            if(columnIndex % 2)
            {
                textureDataGreen[rowIndex * 4096 + columnIndex] = textureData[rowIndex * 4096 + columnIndex];
                textureDataGreen[rowIndex * 4096 + columnIndex - 1] = textureData[rowIndex * 4096 + columnIndex];
            }
            else
            {
                textureDataRed[rowIndex * 4096 + columnIndex] = textureData[rowIndex * 4096 + columnIndex];
                textureDataRed[rowIndex * 4096 + columnIndex + 1] = textureData[rowIndex * 4096 + columnIndex];

                if(columnIndex == 4094)
                {
                    memcpy((unsigned short*)&textureDataRed[(rowIndex + 1) * 4096], (unsigned short*)&textureDataRed[(rowIndex) * 4096], 4096 * sizeof(unsigned short));
                }
            }
        }
    }

    qDebug() << "Extract red/green: " <<  timer.elapsed();
    timer.restart();

    for(int rowIndex = 1; rowIndex < 3072; rowIndex += 2)
    {
        for(int columnIndex = 0; columnIndex < 4096; columnIndex++)
        {
            if(columnIndex % 2)
            {
                textureDataBlue[rowIndex * 4096 + columnIndex] = textureData[rowIndex * 4096 + columnIndex];
                textureDataBlue[rowIndex * 4096 + columnIndex - 1] = textureData[rowIndex * 4096 + columnIndex];

                if(columnIndex == 4095)
                {
                    memcpy((unsigned short*)&textureDataBlue[(rowIndex - 1) * 4096], (unsigned short*)&textureDataBlue[rowIndex * 4096], 4096 * sizeof(unsigned short));
                }
            }
            else
            {
                textureDataGreen[rowIndex * 4096 + columnIndex] = textureData[rowIndex * 4096 + columnIndex];
                textureDataGreen[rowIndex * 4096 + columnIndex + 1] = textureData[rowIndex * 4096 + columnIndex];
            }
        }
    }

    qDebug() << "Extract green/blue: " <<  timer.elapsed();

//    //Fill missing pixels arrays
//    for(int rowIndex = 0; rowIndex < 3072; rowIndex++)
//    {
//        for(int columnIndex = 0; columnIndex < 4096; columnIndex++)
//        {
//            // Copy data from previous row to every second arrow
//            if(columnIndex % 2 != 0)
//            {
//                memcpy((unsigned short*)&textureDataRed[columnIndex * 4096], (unsigned short*)&textureDataRed[(columnIndex - 1) * 4096], 4096 * sizeof(unsigned short));
//                continue;
//            }

//            // Copy values to next empty cell
//            textureDataRed[rowIndex * 4096 + columnIndex + 1] = textureDataRed[rowIndex * 4096 + columnIndex];
//        }
//    }

//    for(int rowIndex = 1; rowIndex < 3072; rowIndex += 2)
//    {
//        for(int columnIndex = 1; columnIndex < 4096; columnIndex += 2)
//        {
//            // Copy data from previous row to every second arrow
//            if(rowIndex % 2 == 0 && columnIndex == 0)
//            {
//                memcpy((unsigned short*)&textureDataBlue[columnIndex * 4096 - 2], (unsigned short*)&textureDataBlue[(columnIndex - 1) * 4096], 4096);
//                continue;
//            }

//            // Copy values to next empty cell
//            textureDataBlue[rowIndex * 4096 + columnIndex] = textureDataBlue[rowIndex * 4096 + columnIndex + 1];
//        }
//    }

    //    std::thread t1(task1, 4000, 0 , 4095);
    //    std::thread t2(task1, 0, 4096, 4095);

    //    t1.join();
    //    t2.join();

    //img->loadFromData((const char*)pixels2);
    //pixels = pixels2;
    //pixels[j] = qRgb(0, pixel1, 0);

    //    for(unsigned int y = 0; y < 3071; y++)
    //    {
    //        for(unsigned x = 0; x < 4095; x += 2)
    //        {
    //            uint16_t pixel1 = (imageData.constData()[(x * y + x) + 1] << 4) + ((imageData.constData()[(x * y + x)] & 0xF0) >> 4);
    //            pixel1 &= 0xFFF;

    //            uint16_t pixel2 = ((imageData.constData()[(x * y + x) + 2] & 0x0F) << 8) + imageData.constData()[(x * y + x) + 1];

    //            pixels[(x * y) + x] = qRgb(pixel1, pixel1, pixel1);
    //            pixels[(x * y) + x + 1] = qRgb(pixel2, pixel2, pixel2);

    //        }
    //    }
    int i = 0;
}
