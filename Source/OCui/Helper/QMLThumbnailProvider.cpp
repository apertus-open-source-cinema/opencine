// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "QMLThumbnailProvider.h"

#include <memory>

#include <Image/BilinearDebayer.h>
#include "Memory/StaticAllocator.h"

//#include <QtAV/AVDemuxer.h>
//#include <QtAV/VideoDecoder.h>

using namespace OC::DataProvider;


//QtAV::AVDemuxer* demux;
//QtAV::VideoDecoder* dec;

QMLThumbnailProvider::QMLThumbnailProvider() : QQuickImageProvider(ImageType::Image),
    _provider(std::make_shared<ImageProvider>()),
    _thumbnailProvider(nullptr)
{
//    demux = new QtAV::AVDemuxer();
//    dec = QtAV::VideoDecoder::create();

    _allocator = new RawPoolAllocator(512 * 1024 * 1024);
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

    OCImage* _image = new OCImage();
    //_image.reset(new OCImage());

    if (id.toLower().endsWith(".dng"))
    {
        _provider->Load(id.toStdString(), FileFormat::DNG, *_image, *_allocator);
    }
    else if(id.toLower().endsWith(".mlv"))
    {
        _provider->Load(id.toStdString(), FileFormat::MLV, *_image, *_allocator);
    }
    else if(id.toLower().endsWith(".mov"))
    {
//        if (!dec) {
//            return image;
//        }

//        demux->setMedia(id);
//        if (!demux->load()) {
//            qWarning("Failed to load file: %s", id.toUtf8().constData());
//            return image;
//        }

//        dec->setCodecContext(demux->videoCodecContext());
//        dec->open();

//        int vstream = demux->videoStream();
//        while (!demux->atEnd())
//        {
//            if (!demux->readFrame())
//                continue;
//            if (demux->stream() != vstream)
//                continue;
//            const QtAV::Packet pkt = demux->packet();
//            if (dec->decode(pkt)) {

//                QtAV::VideoFrame frame = dec->frame();
//                // Increased requestedSize to get clear image when zooming in
                // TODO: Check aspect ratio, seems a bit incorrect
//                image = frame.toImage(QImage::Format_RGB32, requestedSize * 2);

//                break;
//            }
//        }

        return image;
    }
    else
    {
        return image;
    }

    BilinearDebayer* debayer = new BilinearDebayer(*_image);
    debayer->Process();
    delete debayer;

    unsigned int dataLength = _image->Width() * _image->Height();
    unsigned char* interleavedArray = new unsigned char[dataLength * 3];
    unsigned int i = 0;

    for (; i < dataLength; i++)
    {
        interleavedArray[i * 3] = (static_cast<unsigned short*>(_image->RedChannel())[i] - 2052 / 3) >> 6;
        interleavedArray[i * 3 + 1] = (static_cast<unsigned short*>(_image->GreenChannel())[i] - 2052 / 3) >> 6;
        interleavedArray[i * 3 + 2] = (static_cast<unsigned short*>(_image->BlueChannel())[i] - 2052 / 3) >> 6;
    }

    image = QImage(interleavedArray, _image->Width(), _image->Height(), QImage::Format_RGB888);

    // Increased requestedSize to get clear image when zooming in
    image = image.scaled(requestedSize.width() * 2, requestedSize.height() * 2, Qt::KeepAspectRatio);

    delete[] interleavedArray;
    delete _image;

    return image;
}
