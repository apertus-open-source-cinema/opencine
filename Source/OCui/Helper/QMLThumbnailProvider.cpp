#include "QMLThumbnailProvider.h"

#include <memory>

#include <Image/BilinearDebayer.h>
#include "Memory/StaticAllocator.h"

using namespace OC::DataProvider;

QMLThumbnailProvider::QMLThumbnailProvider() : QQuickImageProvider(ImageType::Image),
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

QImage QMLThumbnailProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
	QImage image;

	if (!id.endsWith(".dng"))
	{
        return image;
	}

	_image.reset(new OCImage());

	IAllocator* allocator = new RawPoolAllocator(50 * 1024 * 1024);
	provider->Load(id.toStdString(), FileFormat::DNG, *_image.get(), *allocator);

	BilinearDebayer* debayer = new BilinearDebayer(*_image.get());
	debayer->Process();
	delete debayer;

	unsigned int dataLength = _image->Width() * _image->Height();
	unsigned char* interleavedArray = new unsigned char[dataLength * 3];
	unsigned int i = 0;

	for (; i < dataLength; i++)
	{
		interleavedArray[i * 3] = static_cast<unsigned short*>(_image->RedChannel())[i] >> 4;
		interleavedArray[i * 3 + 1] = static_cast<unsigned short*>(_image->GreenChannel())[i] >> 4;
		interleavedArray[i * 3 + 2] = static_cast<unsigned short*>(_image->BlueChannel())[i] >> 4;
	}

	image = QImage(interleavedArray, _image->Width(), _image->Height(), QImage::Format_RGB888);

	image = image.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);

	delete[] interleavedArray;
	return image;
}
