#include "QMLThumbnailProvider.h"

QMLThumbnailProvider::QMLThumbnailProvider() : QQuickImageProvider(ImageType::Pixmap)
{
    _thumbnailProvider = new OC::DataProvider::ThumbnailProvider();
}

QMLThumbnailProvider::~QMLThumbnailProvider()
{
    if(_thumbnailProvider != nullptr)
    {
        delete _thumbnailProvider;
    }
}

QPixmap QMLThumbnailProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 100;
    int height = 50;

    if (size)
        *size = QSize(width, height);
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);
    pixmap.fill(QColor(id).rgba());

    return pixmap;
}
