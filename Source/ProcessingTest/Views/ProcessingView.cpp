 #include "ProcessingView.h"
#include "ui_ProcessingView.h"

#include <fstream>
#include <thread>

#include <xmmintrin.h>
#include <emmintrin.h>

#include <QFile>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QTime>
#include <QTimer>

#include "Controls/PreviewPane.h"

#include "Image/BayerFrameProcessor.h"

//unsigned char* imageData;
//unsigned short* textureData;

//unsigned short texPixels[4] =
//{
//    32000, 0, 16000, 8000
//};

//QImage* img;

ProcessingView::ProcessingView(QWidget *parent) :
    ui(new Ui::ProcessingView)
{
    ui->setupUi(this);

//    quint32 a[256];
//    quint32 b[256];
//    quint32 c[256];

//    for (int i = 0; i < 256; i += 4)
//    {
//        __m128i vectorA = _mm_loadu_si128((__m128i*)&a[i]);
//        __m128i vectorB = _mm_loadu_si128((__m128i*)&b[i]);
//        __m128i vectorC = _mm_add_epi32(vectorA, vectorB);
//        _mm_storeu_si128((__m128i*)&c[i], vectorC);
//    }

    //LoadTexture();

    //    img  = new QImage(4096, 3072, QImage::Format_RGB32);
    //    QRgb* pixels = reinterpret_cast<QRgb*>(img->bits());

    //    //    memcpy(pixels, imageData, 4096 * 3072);

    //    //    QTime myTimer;
    //    //    myTimer.start();

    //    //    //uchar* pixels2 = new uchar[4096 * 3072 * 2];


    //    int j = 0;
    //    int currentColor = 0;
    //    int imageSize = 4096 * 3072 * 1.5;
    //    for (long long i=0;i < imageSize; i += 3)
    //    {
    //        uint16_t pixel1 = (imageData[i + 1] << 4) + ((imageData[i] & 0xF0) >> 4);
    //        pixel1 &= 0xFFF;

    //        uint16_t pixel2 = ((imageData[i + 2] & 0x0F) << 8) + imageData[i + 1];

    //        //pixels[j] = qRgb(pixel1, pixel1, pixel1);        //pixels2[i] = pixel1;
    //        //pixels[j + 1] = qRgb(pixel2, pixel2, pixel2);
    //        //pixels2[i + 1] = pixel2;

    //        //        currentColor = bayerMatrixRGGB[i / 4096 % 2][(i / 3072) % 2];
    //        //        if(currentColor == 0)
    //        //        {
    //        //            pixels[j] = qRgb(pixel1, 0, 0);
    //        //        }
    //        //        else if(currentColor == 1)
    //        //        {
    //        //            pixels[j] = qRgb(0, pixel1, 0);
    //        //        }
    //        //        else if(currentColor == 2)
    //        //        {
    //        //            pixels[j] = qRgb(0, 0, pixel1);
    //        //        }

    //        //        pixels[j + 1] = qRgb(0, pixel2, pixel2);
    //        //        currentColor = bayerMatrixRGGB[i / 4096 % 2 + 1][(i / 3072 + 1) % 2];
    //        //        if(currentColor == 0)
    //        //        {
    //        //            pixels[j + 1] = qRgb(pixel1, 0, 0);
    //        //        }
    //        //        else if(currentColor == 1)
    //        //        {
    //        //            pixels[j + 1] = qRgb(0, pixel1, 0);
    //        //        }
    //        //        else if(currentColor == 2)
    //        //        {
    //        //            pixels[j + 1] = qRgb(0, 0, pixel1);
    //        //        }

    //        j += 2;
    //    }
}

ProcessingView::~ProcessingView()
{
    delete ui;
}

char bayerMatrixRGGB[2][2] = {{0, 1},
                              {1, 2}
                             };

bool init = false;

void ProcessingView::paintEvent(QPaintEvent *)
{
//    QPainter painter(this);
//    QRect geo = this->geometry();

//    int x, y, width, height;

//    x = geo.x()+10;
//    y = geo.y()+10;
//    width = geo.width()-10;
//    height = geo.height()-10;

//    painter.fillRect(x, y, width, height, QColor(220,220,220));

//    painter.drawText(x+10, y+10, "Machine " + QString::number(12345));

//    if(!init)
//    {
//        QTime timer;
//        timer.start();

//        int length;

//        std::ifstream is;
//        is.open ("axiom.raw12", std::ios::binary );

//        // get length of file:
//        is.seekg (0, std::ios::end);
//        length = is.tellg();
//        is.seekg (0, std::ios::beg);

//        // allocate memory:
//        unsigned char* imageData = new unsigned char [length];

//        // read data as a block:
//        is.read ((char*)imageData,length);
//        is.close();

//        qDebug() << "File loading: " <<  timer.elapsed();
//        timer.restart();

//        std::unique_ptr<IFrameProcessor> frameProcessor(new BayerFrameProcessor());

//        frameProcessor->SetData(*imageData, 4096, 3072, SourceFormat::Integer12);
//        frameProcessor->Process();

//        qDebug() << "Process(): " <<  timer.elapsed();
//        timer.restart();

//        unsigned short* textureDataRed = frameProcessor->GetDataRed();
//        unsigned short* textureDataGreen = frameProcessor->GetDataGreen();
//        unsigned short* textureDataBlue = frameProcessor->GetDataBlue();

        //ui->openGLWidget->SetTextureRed(4096, 3072, textureDataRed);
        //ui->openGLWidget->SetTextureGreen(4096, 3072, textureDataGreen);
        //ui->openGLWidget->SetTextureBlue(4096, 3072, textureDataBlue);

//        qDebug() << "Data to OpenGL: " <<  timer.elapsed();
//        timer.restart();

//        textureDataRed = frameProcessor->GetDataRed();
//        textureDataGreen = frameProcessor->GetDataGreen();
//        textureDataBlue = frameProcessor->GetDataBlue();

//        ui->openGLWidget->SetTextureRed(4096, 3072, textureDataRed);
//        ui->openGLWidget->SetTextureGreen(4096, 3072, textureDataGreen);
//        ui->openGLWidget->SetTextureBlue(4096, 3072, textureDataBlue);

//        qDebug() << "Data to OpenGL(2nd run): " <<  timer.elapsed();

//        init = true;
//    }

    //img->loadFromData((const char*)imageData);
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
    //painter.scale(0.3, 0.3);
    //painter.drawImage(0, 0, *img);

    //ui->openGLWidget->SetTexture(2, 2, texPixels);
}

void ProcessingView::SetFrame(OCImage &image)
{
    testImage = &image;
    int i = 0;

    if(testImage != nullptr && ui->openGLWidget->isValid())
    {
        ui->openGLWidget->SetTextureRed(testImage->Width(), testImage->Height(), (unsigned short*)testImage->RedChannel());
        ui->openGLWidget->SetTextureGreen(testImage->Width(), testImage->Height(), (unsigned short*)testImage->GreenChannel());
        ui->openGLWidget->SetTextureBlue(testImage->Width(), testImage->Height(), (unsigned short*)testImage->BlueChannel());
    }
    //this->repaint();
    //ui->openGLWidget->SetTextureRed(image.Width(), image.Height(), (unsigned short*)image.RedChannel());
    //ui->openGLWidget->SetTextureGreen(4096, 3072, textureDataGreen);
    //ui->openGLWidget->SetTextureBlue(4096, 3072, textureDataBlue);
}

//void task1(int value, int offset, int length)
//{
//    QTime timer;
//    timer.start();

//    for(int i = offset; i < offset + length; i++)
//    {
//        textureData[i] = value;
//    }

//    qDebug() << value << " elapsed: " <<  timer.elapsed();
//}

//void ExtractRedGreenNoInterpolation()
//{
//    unsigned int rowIndex = 0;
//    unsigned int columnIndex = 0;

//    for(rowIndex = 0; rowIndex < 3072; rowIndex += 2)
//    {
//        for(columnIndex = 0; columnIndex < 4096; columnIndex+=2)
//        {
//            textureDataGreen[rowIndex * 4096 + columnIndex + 1] = textureData[rowIndex * 4096 + columnIndex + 1];
//            textureDataRed[rowIndex * 4096 + columnIndex] = textureData[rowIndex * 4096 + columnIndex];
//        }
//    }
//}

//void ExtractGreenBlueNoInterpolation()
//{
//    unsigned int rowIndex = 1;
//    unsigned int columnIndex = 0;

//    for(rowIndex = 1; rowIndex < 3072; rowIndex += 2)
//    {
//        for(columnIndex = 0; columnIndex < 4096; columnIndex+=2)
//        {
//            textureDataBlue[rowIndex * 4096 + columnIndex + 1] = textureData[rowIndex * 4096 + columnIndex + 1];
//            textureDataGreen[rowIndex * 4096 + columnIndex] = textureData[rowIndex * 4096 + columnIndex];
//        }
//    }
//}

void ProcessingView::LoadTexture()
{
    //QFile file("axiom.raw12");
    //if (!file.open(QIODevice::ReadOnly)) return;
    //imageData = file.readAll().data();

    //textureData = new unsigned short[4096 * 3072];

    //uchar* pixels2 = new uchar[4096 * 3072 * 2];

    //    QTime timer;
    //    timer.start();

    //    int j = 0;
    //    int currentColor = 0;
    //    for (long long i=0;i < length; i += 3)
    //    {
    //        uint16_t pixel1 = (imageData[i] << 4) + ((imageData[i + 1] & 0xF0) >> 4);
    //        pixel1 &= 0xFFF;

    //        uint16_t pixel2 = ((imageData[i + 1] & 0x0F) << 8) + imageData[i + 2];

    //        textureData[j] = pixel1;
    //        textureData[j + 1] = pixel2;

    //        j += 2;
    //    }
    //    qDebug() << "Convert bits 12 -> 16: " <<  timer.elapsed();




    //    timer.restart();

    ////    ExtractRedGreen();
    ////    ExtractGreenBlue();

    //    qDebug() << "Extract colors: " <<  timer.elapsed();

    //    memset(textureDataRed, 0, 4096*3072 * sizeof(unsigned short));
    //    memset(textureDataGreen, 0, 4096*3072 * sizeof(unsigned short));
    //    memset(textureDataBlue, 0, 4096*3072 * sizeof(unsigned short));

    //    timer.restart();

    //    std::thread t1(ExtractRedGreen);
    //    std::thread t2(ExtractGreenBlue);

    //    t1.join();
    //    t2.join();

    //qDebug() << "Extract colors (2 threads): " <<  timer.elapsed();

    //    memset(textureDataRed, 0, 4096*3072 * sizeof(unsigned short));
    //    memset(textureDataGreen, 0, 4096*3072 * sizeof(unsigned short));
    //    memset(textureDataBlue, 0, 4096*3072 * sizeof(unsigned short));

    //    timer.restart();

    //    std::thread t3(ExtractRedGreenNoInterpolation);
    //    std::thread t4(ExtractGreenBlueNoInterpolation);

    //    t3.join();
    //    t4.join();

    //    qDebug() << "Extract colors (2 threads, no interpolation): " <<  timer.elapsed();




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

void ProcessingView::on_pushButton_toggled(bool checked)
{
    ui->openGLWidget->SwitchRedChannel(checked);
}

void ProcessingView::on_pushButton_3_toggled(bool checked)
{
    ui->openGLWidget->SwitchGreenChannel(checked);
}

void ProcessingView::on_pushButton_4_toggled(bool checked)
{
    ui->openGLWidget->SwitchBlueChannel(checked);
}
