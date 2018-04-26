// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "BayerFrameDownscaler.h"

#include <omp.h>
#include <thread>

#include <Log/Logger.h>

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
        BayerFrameDownscaler::Convert12To16Bit();
        break;
    case ImageFormat::Integer14:
        OC_LOG_INFO("14->16bit conversion");
        BayerFrameDownscaler::Convert14To16Bit();
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

void BayerFrameDownscaler::Convert12To16Bit() const
{
    int j = 0;
    int dataSize = static_cast<int>(_size * 1.5f); //12bit / 8bit

    //Take every 3 bytes to extract 2 x 12bits
    for (long long index = 0; index < dataSize; index += 3)
    {
        uint32_t mergedBytes = (static_cast<uint32_t>(_data[index + 0]) << 16) +
                (static_cast<uint32_t>(_data[index + 1]) << 8) +
                static_cast<uint32_t>(_data[index + 2]);

        _outputData[j + 1] = static_cast<uint16_t>(mergedBytes & 0xFFF);
        _outputData[j] = static_cast<uint16_t>((mergedBytes >> 12) & 0xFFF);

        j += 2;
    }
}

void BayerFrameDownscaler::Convert14To16Bit() const
{
    int j = 0;
    int dataSize = static_cast<int>((_width * 1.75) * _height); // 14bit / 8bit

    // Process 8 bytes at once to get 4 pixels of 14 bits
    //#pragma omp parallel for
    for (long index = 0; index < dataSize; index += 14)
    {
        uint64_t mergedBytes1 = (static_cast<uint64_t>(_data[index]) << 48) +
                (static_cast<uint64_t>(_data[index + 1]) << 56) +
                (static_cast<uint64_t>(_data[index + 2]) << 32) +
                (static_cast<uint64_t>(_data[index + 3]) << 40) +
                (static_cast<uint64_t>(_data[index + 4]) << 16) +
                (static_cast<uint64_t>(_data[index + 5]) << 24) +
                (static_cast<uint64_t>(_data[index + 6])) +
                static_cast<uint64_t>(_data[index + 7] << 8);

        uint64_t mergedBytes2 = (static_cast<uint64_t>(_data[index + 8]) << 32) +
                (static_cast<uint64_t>(_data[index + 9]) << 40) +
                (static_cast<uint64_t>(_data[index + 10]) << 16) +
                (static_cast<uint64_t>(_data[index + 11]) << 24) +
                (static_cast<uint64_t>(_data[index + 12])) +
                static_cast<uint64_t>(_data[index + 13] << 8);

        // Processing bytes in reversed order, so it resembles the shifting of uint64_t to the right
        _outputData[j + 7] = static_cast<uint16_t>(mergedBytes2 & 0x3FFF);
        _outputData[j + 6] = static_cast<uint16_t>((mergedBytes2 >> 14) & 0x3FFF);
        _outputData[j + 5] = static_cast<uint16_t>((mergedBytes2 >> 28) & 0x3FFF);
        _outputData[j + 4] = static_cast<uint16_t>((mergedBytes1 << 6) & 0x3FC0) + static_cast<uint16_t>((mergedBytes2 >> 42) & 0x3F);

        // Offset: 6 bits
        _outputData[j + 3] = static_cast<uint16_t>(mergedBytes1 >> 8) & 0x3FFF;
        _outputData[j + 2] = static_cast<uint16_t>(mergedBytes1 >> 22) & 0x3FFF;
        _outputData[j + 1] = static_cast<uint16_t>(mergedBytes1 >> 36) & 0x3FFF;
        _outputData[j] = static_cast<uint16_t>(mergedBytes1 >> 50) & 0x3FFF;

        j += 8;
    }
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
