#ifndef QMLTHUMBNAILPROVIDER_H
#define QMLTHUMBNAILPROVIDER_H

#include <QQuickImageProvider>

#include <Image/ThumbnailProvider.h>

#include "OCui_export.h"

class OCUI_EXPORT QMLThumbnailProvider : public QQuickImageProvider
{
    OC::DataProvider::ThumbnailProvider* _thumbnailProvider;

public:
    QMLThumbnailProvider();
    ~QMLThumbnailProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif //QMLTHUMBNAILPROVIDER_H
