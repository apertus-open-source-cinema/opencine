#ifndef QMLTHUMBNAILPROVIDER_H
#define QMLTHUMBNAILPROVIDER_H

#include <QQuickImageProvider>

#include <memory>

#include <Image/ImageProvider.h>
#include <Image/OCImage.h>
#include <Image/ThumbnailProvider.h>

#include "OCui_export.h"


class OCUI_EXPORT QMLThumbnailProvider : public QQuickImageProvider
{
	OC::DataProvider::ThumbnailProvider* _thumbnailProvider;
    std::shared_ptr<OC::DataProvider::ImageProvider> _provider;

	std::unique_ptr<OC::DataProvider::OCImage> _image;

    IAllocator* _allocator;

public:
	QMLThumbnailProvider();
	~QMLThumbnailProvider();

public:
	QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif //QMLTHUMBNAILPROVIDER_H
