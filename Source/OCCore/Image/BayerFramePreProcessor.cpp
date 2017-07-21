#include "BayerFramePreProcessor.h"

#include <omp.h>
#include <thread>

#include <Log/Logger.h>

void BayerFramePreProcessor::MapPatternToData()
{
    switch (_pattern)
    {
    case BayerPattern::RGGB:
        dataUL = _dataRed;
        dataUR = _dataGreen;
        dataLL = _dataGreen;
        dataLR = _dataBlue;
        break;
    case BayerPattern::BGGR:
        dataUL = _dataBlue;
        dataUR = _dataGreen;
        dataLL = _dataGreen;
        dataLR = _dataRed;
        break;
    case BayerPattern::GRBG:
        dataUL = _dataGreen;
        dataUR = _dataRed;
        dataLL = _dataBlue;
        dataLR = _dataGreen;
        break;
    case BayerPattern::GBRG:
        dataUL = _dataGreen;
        dataUR = _dataBlue;
        dataLL = _dataRed;
        dataLR = _dataGreen;
        break;
    }
}

void BayerFramePreProcessor::ExtractOddRows() const
{
    //#pragma omp parallel for schedule(dynamic,1)
    for (unsigned int rowIndex = 0; rowIndex < _height; rowIndex += 2)
    {
        for (unsigned int columnIndex = 0; columnIndex < _width; columnIndex++)
        {
            if (columnIndex % 2)
            {
                dataUR[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
            }
            else
            {
                dataUL[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
            }
        }
    }

    OC_LOG_INFO("OddRows threads: " + std::to_string(omp_get_num_threads()));
}

void BayerFramePreProcessor::ExtractEvenRows() const
{
    //#pragma omp parallel for schedule(dynamic,1)
    for (unsigned int rowIndex = 1; rowIndex < _height; rowIndex += 2)
    {
        for (unsigned int columnIndex = 0; columnIndex < _width; columnIndex++)
        {
            if (columnIndex % 2)
            {
                dataLR[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
            }
            else
            {
                dataLL[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
            }
        }
    }

    OC_LOG_INFO("EvenRows threads: " + std::to_string(omp_get_num_threads()));
}

BayerFramePreProcessor::BayerFramePreProcessor() :
    _data(nullptr),
    _outputData(nullptr),
    _size(0),
    dataUL(nullptr),
    dataUR(nullptr),
    dataLL(nullptr),
    dataLR(nullptr),
    _dataRed(nullptr),
    _dataGreen(nullptr),
    _dataBlue(nullptr),
    _width(0),
    _height(0)
{
}

BayerFramePreProcessor::~BayerFramePreProcessor()
{
}

// TODO: Add parameter of data length, it would simplify some processing
void BayerFramePreProcessor::SetData(uint8_t* data, OCImage& image, ImageFormat imageFormat)
{
    _data = data;

    _width = image.Width();
    _height = image.Height();

    _size = _width * _height;

    _outputData = new uint16_t[_size];

    _dataRed = static_cast<uint16_t*>(image.RedChannel());
    _dataGreen = static_cast<uint16_t*>(image.GreenChannel());
    _dataBlue = static_cast<uint16_t*>(image.BlueChannel());

    _imageFormat = imageFormat;
    _pattern = image.GetBayerPattern();

    MapPatternToData();
}

void BayerFramePreProcessor::Process()
{


    std::thread t0;
    switch(_imageFormat)
    {
    case ImageFormat::Integer12:
        OC_LOG_INFO("12->16bit conversion");
        t0 = std::thread(&BayerFramePreProcessor::Convert12To16Bit, this);
        break;
    case ImageFormat::Integer14:
        OC_LOG_INFO("14->16bit conversion");
        t0 = std::thread(&BayerFramePreProcessor::Convert14To16Bit, this);
        break;
    case ImageFormat::Unknown:
    case ImageFormat::Integer16:
        break;
    }

    t0.join();

    std::thread t1(&BayerFramePreProcessor::ExtractOddRows, this);
    std::thread t2(&BayerFramePreProcessor::ExtractEvenRows, this);

    OC_LOG_INFO("Extract rows");
    t1.join();
    t2.join();

    //OC_LOG_INFO("Extract finished");
}

void BayerFramePreProcessor::Convert12To16Bit() const
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

void BayerFramePreProcessor::Convert14To16Bit() const
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

uint16_t*BayerFramePreProcessor::GetDataRed()
{
    return _dataRed;
}

uint16_t*BayerFramePreProcessor::GetDataGreen()
{
    return _dataGreen;
}

uint16_t*BayerFramePreProcessor::GetDataBlue()
{
    return _dataBlue;
}

void BayerFramePreProcessor::SetLinearizationData(uint16_t* linearizationTable, unsigned int linearizationLength)
{
    _linearizationTable = linearizationTable;
    _linearizationLength = linearizationLength;
}
