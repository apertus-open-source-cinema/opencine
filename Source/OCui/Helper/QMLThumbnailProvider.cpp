#include "QMLThumbnailProvider.h"

#include <memory>

#include <Image/BilinearDebayer.h>

using namespace OC::DataProvider;

QMLThumbnailProvider::QMLThumbnailProvider() : QQuickImageProvider(ImageType::Image),
//_thumbnailProvider(new OC::DataProvider::ThumbnailProvider());
provider(std::unique_ptr<ImageProvider>()),
_thumbnailProvider(nullptr)
{
}

QMLThumbnailProvider::~QMLThumbnailProvider()
{
	if (_thumbnailProvider != nullptr)
	{
		delete _thumbnailProvider;
	}
}

//QPixmap QMLThumbnailProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
//{
//    QPixmap pixmap;

////    if(!id.endsWith(".dng"))
////    {
////        pixmap = QPixmap::from
////        return ;
////    }

////    int width = 100;
////    int height = 50;

////    if (size)
////        *size = QSize(width, height);
////    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
////                   requestedSize.height() > 0 ? requestedSize.height() : height);
////    pixmap.fill(QColor(id).rgba());

//    std::shared_ptr<OCImage> _image = std::make_shared<OCImage>();
//    std::unique_ptr<ImageProvider> provider = std::unique_ptr<ImageProvider>();
//    provider->Load("Shot 1/Frame000320.dng", FileFormat::DNG, *_image.get());

//    BilinearDebayer* debayer = new BilinearDebayer(*_image.get());
//    debayer->Process();

//    unsigned int dataLength = _image->Width() * _image->Height();
//    unsigned char* interleavedArray = new unsigned char[dataLength * 3];
//    unsigned int i = 0;

//    for(; i < dataLength; i++)
//    {
//        interleavedArray[i * 3] = ((unsigned short*)_image->RedChannel())[i] >> 8;
//        interleavedArray[i * 3 + 1] = ((unsigned short*)_image->GreenChannel())[i] >> 8;
//        interleavedArray[i * 3 + 2] = ((unsigned short*)_image->BlueChannel())[i] >> 8;
//    }

//    QImage *image = new QImage(interleavedArray, _image->Width(), _image->Height(), QImage::Format_RGB888);

//    pixmap.fromImage(*image);
//    return pixmap;
//}

QImage QMLThumbnailProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
	QImage image;

	if (!id.endsWith(".dng"))
	{
		return image;
	}

	_image.reset(new OCImage());

	provider->Load(id.toStdString(), FileFormat::DNG, *_image.get());

	BilinearDebayer* debayer = new BilinearDebayer(*_image.get());
	debayer->Process();
	delete debayer;

	unsigned int dataLength = _image->Width() * _image->Height();
	unsigned char* interleavedArray = new unsigned char[dataLength * 3];
	unsigned int i = 0;

	for (; i < dataLength; i++)
	{
		interleavedArray[i * 3] = ((unsigned short*)_image->RedChannel())[i] >> 8;
		interleavedArray[i * 3 + 1] = ((unsigned short*)_image->GreenChannel())[i] >> 8;
		interleavedArray[i * 3 + 2] = ((unsigned short*)_image->BlueChannel())[i] >> 8;
	}

	image = QImage(interleavedArray, _image->Width(), _image->Height(), QImage::Format_RGB888);

	image = image.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);

	delete[] interleavedArray;
	return image;
}