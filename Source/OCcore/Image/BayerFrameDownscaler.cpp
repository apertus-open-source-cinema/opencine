// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "BayerFrameDownscaler.h"

#include <omp.h>
#include <thread>

#include <Log/Logger.h>

#include "ImageHelper.h"

void BayerFrameDownscaler::Extract(int jump) const
{
    unsigned int index;
    int dataIndex = 0;
    for (index = 0; index < _size; index += jump)
    {

        _dataRed[dataIndex] = _outputData[index + _width];
        _dataGreen[dataIndex] = (_outputData[index] + _outputData[index + 1 + _width]) >> 1;
        _dataBlue[dataIndex] = _outputData[index + 1];
        dataIndex++;
        if ((index + jump) % _width == 0)
        {
            index += (jump - 1) * _width;
        }
    }
    OC_LOG_INFO("R: " + std::to_string(sizeof(_dataRed)/sizeof(*_dataRed)) + " G: " + std::to_string(sizeof(_dataGreen)/sizeof(*_dataGreen)) + " B: " + std::to_string(sizeof(_dataBlue)/sizeof(*_dataBlue)) + " index: " + std::to_string(index));

}

BayerFrameDownscaler::BayerFrameDownscaler() :
    _data(nullptr),
    _outputData(nullptr),
    _size(0),
    _dataRed(nullptr),
    _dataGreen(nullptr),
    _dataBlue(nullptr),
    _width(0),
    _height(0)
{
}

BayerFrameDownscaler::~BayerFrameDownscaler()
{
}

// TODO: Add parameter of data length, it would simplify some processing
void BayerFrameDownscaler::SetData(uint8_t* data, OCImage& image, ImageFormat imageFormat)
{
    _data = data;

    _width = image.Width();
    _height = image.Height();

    _size = _width * _height;


    // Changes the resolution to half the width and height.
    image.SetWidth(image.Width()/2);
    image.SetHeight(image.Height()/2);

    _outputData = new uint16_t[_size];

    _dataRed = static_cast<uint16_t*>(image.RedChannel());
    _dataGreen = static_cast<uint16_t*>(image.GreenChannel());
    _dataBlue = static_cast<uint16_t*>(image.BlueChannel());

    _imageFormat = imageFormat;
    _pattern = image.GetBayerPattern();

    OC_LOG_INFO("Width: " + std::to_string(_width) + " Height: " + std::to_string(_height));
}

void BayerFrameDownscaler::Process()
{
    switch(_imageFormat)
    {
    case ImageFormat::Integer12:
        OC_LOG_INFO("12->16bit conversion");
        OC::Image::ImageHelper::Convert12To16Bit(_data, _width, _height, _outputData);
        break;
    case ImageFormat::Integer14:
        OC_LOG_INFO("14->16bit conversion");
        OC::Image::ImageHelper::Convert14To16Bit(_data, _width, _height, _outputData);
        break;
    case ImageFormat::Unknown:
    case ImageFormat::Integer16:
        break;
    }

    OC_LOG_INFO("Extracting");

    // It currently skips 4 pixels (half the width and height), 2 is normal.
    BayerFrameDownscaler::Extract(2);

    //OC_LOG_INFO("Extract finished");
}

uint16_t*BayerFrameDownscaler::GetDataRed()
{
    return _dataRed;
}

uint16_t*BayerFrameDownscaler::GetDataGreen()
{
    return _dataGreen;
}

uint16_t*BayerFrameDownscaler::GetDataBlue()
{
    return _dataBlue;
}
