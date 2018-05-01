// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "BayerFramePreProcessor.h"

// TODO: Add openmp package to the ArchLinux section in env_setup.sh
#include <omp.h>
#include <thread>

#include <Log/Logger.h>

#include "ImageHelper.h"

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
    for (unsigned int index = 0; index < _size; index += 2)
    {
        dataUL[index] = _outputData[index];
        dataUR[index + 1] = _outputData[index + 1];
        if ((index + 2) % _width == 0)
            index += _width;
    }

//    OC_LOG_INFO("OddRows threads: " + std::to_string(omp_get_num_threads()));
}

void BayerFramePreProcessor::ExtractEvenRows() const
{
    //#pragma omp parallel for schedule(dynamic,1)
    for (unsigned int index = _width; index < _size; index += 2)
    {
        dataLL[index] = _outputData[index];
        dataLR[index + 1] = _outputData[index + 1];
        if ((index + 2) % _width == 0)
            index += _width;
    }

//    OC_LOG_INFO("EvenRows threads: " + std::to_string(omp_get_num_threads()));
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
    // For benchmarking.
    auto start = std::chrono::high_resolution_clock::now();

    //std::thread t0;
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

    //t0.join();

    std::thread t1(&BayerFramePreProcessor::ExtractOddRows, this);
    std::thread t2(&BayerFramePreProcessor::ExtractEvenRows, this);

//    OC_LOG_INFO("Extract rows");
    t1.join();
    t2.join();

    // For benchmarking.
    auto diffTime = std::chrono::high_resolution_clock::now() - start;
    auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();
    auto log = "PreProcessorTime: " + std::to_string(frameTime) + " ms";
    OC_LOG_INFO(log);

//    OC_LOG_INFO("Extract finished");
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
