#include "OCImage.h"

OC::Image::OCImage::OCImage() :
        _width(0),
        _height(0),
        _pattern(BayerPattern::RGGB),
        _redData(nullptr),
        _greenData(nullptr),
        _blueData(nullptr),
        _dataLength(0)
{
}

OC::Image::OCImage::~OCImage()
{
    delete[](short *) _redData;
    delete[](short *) _greenData;
    delete[](short *) _blueData;
}

void OC::Image::OCImage::SetWidth(unsigned int width)
{
    _width = width;
}

void OC::Image::OCImage::SetHeight(unsigned int height)
{
    _height = height;
}

void *OC::Image::OCImage::RedChannel()
{
    return _redData;
}

void *OC::Image::OCImage::GreenChannel()
{
    return _greenData;
}

void *OC::Image::OCImage::BlueChannel()
{
    return _blueData;
}

void OC::Image::OCImage::SetFormat(OC::Image::ImageFormat format)
{
    _format = format;
}

unsigned int OC::Image::OCImage::Width() const
{
    return _width;
}

unsigned int OC::Image::OCImage::Height() const
{
    return _height;
}

OC::Image::ImageFormat OC::Image::OCImage::Format() const
{
    return _format;
}

OC::Image::ImageType OC::Image::OCImage::Type() const
{
    return _type;
}

void OC::Image::OCImage::SetType(OC::Image::ImageType type)
{
    _type = type;
}

unsigned int OC::Image::OCImage::DataLength() const
{
    return _dataLength;
}

void OC::Image::OCImage::SetRedChannel(void *redData)
{
    _dataLength = _width * _height * sizeof(unsigned short);

    if(_redData == nullptr)
    {
        _redData = new unsigned short[_dataLength];
    }

    memmove(_redData, redData, _dataLength);
}

void OC::Image::OCImage::SetGreenChannel(void *greenData)
{
    if(_greenData == nullptr)
    {
        _greenData = new unsigned short[_dataLength];
    }

    memmove(_greenData, greenData, _dataLength);
}

void OC::Image::OCImage::SetBlueChannel(void *blueData)
{
    if(_blueData == nullptr)
    {
        _blueData = new unsigned short[_dataLength];
    }

    memmove(_blueData, blueData, _dataLength);
}

void OC::Image::OCImage::SetBayerPattern(OC::Image::BayerPattern pattern)
{
    _pattern = pattern;
}

OC::Image::BayerPattern OC::Image::OCImage::GetBayerPattern() const
{
    return _pattern;
}
