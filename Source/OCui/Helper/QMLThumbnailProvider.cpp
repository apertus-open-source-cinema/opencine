#include "QMLThumbnailProvider.h"

#include <memory>

#include <Image/BilinearDebayer.h>
#include "Memory/StaticAllocator.h"

#include <QtAV/AVDemuxer.h>
#include <QtAV/VideoDecoder.h>

using namespace OC::DataProvider;


QtAV::AVDemuxer* demux;
QtAV::VideoDecoder* dec;

QMLThumbnailProvider::QMLThumbnailProvider() : QQuickImageProvider(ImageType::Image),
    provider(std::unique_ptr<ImageProvider>()),
    _thumbnailProvider(nullptr)
{
    demux = new QtAV::AVDemuxer();
    dec = QtAV::VideoDecoder::create();
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

    if (!dec) {
        return image;
    }

    //demux.setMedia("/media/andi/OC_test_disk/ARRI/A007C002_151124_R3VJ.mov");
    demux->setMedia(id);
    if (!demux->load()) {
        qWarning("Failed to load file: %s", id.toUtf8().constData());
        return image;
    }

    dec->setCodecContext(demux->videoCodecContext());
    dec->open();

    int vstream = demux->videoStream();
    while (!demux->atEnd())
    {
        if (!demux->readFrame())
            continue;
        if (demux->stream() != vstream)
            continue;
        const QtAV::Packet pkt = demux->packet();
        if (dec->decode(pkt)) {

            QtAV::VideoFrame frame = dec->frame();
            image = frame.toImage(QImage::Format_ARGB32, requestedSize);

            break;
        }
    }

    return image;

    //    if (!id.endsWith(".dng"))
    //    {
    //        return image;
    //    }

    //    _image.reset(new OCImage());

    //    IAllocator* allocator = new RawPoolAllocator(50 * 1024 * 1024);
    //    provider->Load(id.toStdString(), FileFormat::DNG, *_image.get(), *allocator);

    //    BilinearDebayer* debayer = new BilinearDebayer(*_image.get());
    //    debayer->Process();
    //    delete debayer;

    //    unsigned int dataLength = _image->Width() * _image->Height();
    //    unsigned char* interleavedArray = new unsigned char[dataLength * 3];
    //    unsigned int i = 0;

    //    for (; i < dataLength; i++)
    //    {
    //        interleavedArray[i * 3] = static_cast<unsigned short*>(_image->RedChannel())[i] >> 4;
    //        interleavedArray[i * 3 + 1] = static_cast<unsigned short*>(_image->GreenChannel())[i] >> 4;
    //        interleavedArray[i * 3 + 2] = static_cast<unsigned short*>(_image->BlueChannel())[i] >> 4;
    //    }

    //    image = QImage(interleavedArray, _image->Width(), _image->Height(), QImage::Format_RGB888);

    //    image = image.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);

    //    delete[] interleavedArray;
    //    return image;
}
