// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "BilinearDebayerOMP.h"

// TODO: Add multi-threading.
#include <omp.h>

#include <Log/Logger.h>

BilinearDebayerOMP::BilinearDebayerOMP()
{
    // TODO (BAndiT1983): Add implementation
}

BilinearDebayerOMP::BilinearDebayerOMP(OCImage &image)
{
    _width = image.Width();
    _height = image.Height();
    _size = _width * _height;

    _redChannel = static_cast<uint16_t*>(image.RedChannel());
    _greenChannel = static_cast<uint16_t*>(image.GreenChannel());
    _blueChannel = static_cast<uint16_t*>(image.BlueChannel());

    _pattern = image.GetBayerPattern();
    SetPatternOffsets(_pattern);
}

BilinearDebayerOMP::~BilinearDebayerOMP()
{
}

void BilinearDebayerOMP::DebayerBottomRight(uint16_t *channel)
{
    uint32_t maxCol = _width - 1;
    uint32_t index;
    #pragma omp parallel for collapse(2)
    for(uint32_t row = _patternOffsets[0]; row < _height; row += 2)
    {
        for(uint32_t col = _patternOffsets[1]; col < maxCol; col += 2)
        {
            index = (row * _width) + col;
            channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
            channel[index + 1] = ( channel[index + _width + 1] + channel[index - _width + 1] ) >> 1;
            channel[index + _width] = ( channel[index + _width - 1] + channel[index + _width + 1] ) >> 1;
        }
    }
}

void BilinearDebayerOMP::DebayerBottomLeft(uint16_t *channel)
{
    uint32_t maxCol = _width - 1;
    uint32_t index;
    #pragma omp parallel for collapse(2)
    for(uint32_t row = _patternOffsets[0]; row < _height; row += 2)
    {
        for(uint32_t col = _patternOffsets[1]; col < maxCol; col += 2)
        {
            index = (row * _width) + col;

            channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
            channel[index - 1] = ( channel[index + _width - 1] + channel[index - _width - 1] ) >> 1;
            channel[index + _width] = ( channel[index + _width - 1] + channel[index + _width + 1] ) >> 1;

        }
    }
}

void BilinearDebayerOMP::DebayerGreen0()
{
    uint32_t index;
    #pragma omp parallel for collapse(2)
    for(uint32_t row = _patternOffsets[0]; row < _height; row += 2)
    {
        for(uint32_t col = _patternOffsets[1]; col < _width; col += 2)
        {
            index = (row * _width) + col;

            _greenChannel[index] = ( _greenChannel[index - _width] + _greenChannel[index - 1] + _greenChannel[index + 1] + _greenChannel[index + _width] ) >> 2;
        }
    }
}

void BilinearDebayerOMP::DebayerGreen1()
{
    uint32_t index;
    #pragma omp parallel for collapse(2)
    for(uint32_t row = _patternOffsets[2]; row < _height; row += 2)
    {
        for(uint32_t col = _patternOffsets[3]; col < _width; col += 2)
        {
            index = (row * _width) + col;

            _greenChannel[index] = ( _greenChannel[index - _width] + _greenChannel[index - 1] + _greenChannel[index + 1] + _greenChannel[index + _width] ) >> 2;
        }
    }
}

void BilinearDebayerOMP::DebayerTopLeft(uint16_t *channel)
{
    uint32_t maxCol = _width - 1;
    uint32_t index;
    #pragma omp parallel for collapse(2)
    for(uint32_t row = _patternOffsets[2]; row < _height; row += 2)
    {
        for(uint32_t col = _patternOffsets[3]; col < maxCol; col += 2)
        {
            index = (row * _width) + col;

            channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
            channel[index - 1] = ( channel[index + _width - 1] + channel[index - _width - 1] ) >> 1;
            channel[index - _width] = ( channel[index - _width - 1] + channel[index - _width + 1] ) >> 1;
        }
    }
}

void BilinearDebayerOMP::DebayerTopRight(uint16_t *channel)
{
    uint32_t maxCol = _width - 1;
    uint32_t index;
    #pragma omp parallel for collapse(2)
    for(uint32_t row = _patternOffsets[2]; row < _height; row += 2)
    {
        for(uint32_t col = _patternOffsets[3]; col < maxCol; col += 2)
        {
            index = (row * _width) + col;

            channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
            channel[index + 1] = ( channel[index + _width + 1] + channel[index - _width + 1] ) >> 1;
            channel[index - _width] = ( channel[index - _width - 1] + channel[index - _width + 1] ) >> 1;
        }
    }
}

void BilinearDebayerOMP::DemosaicBorders(uint16_t *channel)
{
    uint32_t size = _size - _width;
    #pragma omp parallel for
    for(uint32_t index = 0; index < _width; index += 2)
    {
        channel[index] = channel[index + _width];
        channel[index + 1] = channel[index + _width + 1];
        channel[size + index] = channel[size + index - _width];
        channel[size + index + 1] = channel[size + index - _width + 1];
    }
    #pragma omp parallel for
    for(uint32_t index = 0; index < _height; index += 2)
    {
        channel[(index * _width)] = channel[(index * _width) + 1];
        channel[(index + 1) * _width] = channel[((index + 1) * _width) + 1];
        channel[((index + 1) * _width) - 1] = channel[((index + 1) * _width) - 2];
        channel[((index + 2) * _width) - 1] = channel[((index + 2) * _width) - 2];
    }
}


void BilinearDebayerOMP::Process(OCImage& image)
{
    _width = image.Width();
    _height = image.Height();
    _size = _width * _height;

    _redChannel = static_cast<uint16_t*>(image.RedChannel());
    _greenChannel = static_cast<uint16_t*>(image.GreenChannel());
    _blueChannel = static_cast<uint16_t*>(image.BlueChannel());

    _pattern = image.GetBayerPattern();
    SetPatternOffsets(_pattern);

    //    OC_LOG_INFO("\nConsidering width as " + std::to_string(_width) + ":\n" + std::to_string(_patternOffsets[0]) + "\n" + std::to_string(_patternOffsets[1]) + "\n" + std::to_string(_patternOffsets[2]) + "\n" + std::to_string(_patternOffsets[3]) + "\n");

    Process();
}

void BilinearDebayerOMP::Process()
{
    switch (_pattern) {
    case BayerPattern::RGGB:
        BilinearDebayerOMP::DebayerBottomRight(_redChannel);
        BilinearDebayerOMP::DebayerTopLeft(_blueChannel);
        break;
    case BayerPattern::BGGR:
        BilinearDebayerOMP::DebayerBottomRight(_blueChannel);
        BilinearDebayerOMP::DebayerTopLeft(_redChannel);
        break;
    case BayerPattern::GRBG:
        BilinearDebayerOMP::DebayerBottomLeft(_redChannel);
        BilinearDebayerOMP::DebayerTopRight(_blueChannel);
        break;
    case BayerPattern::GBRG:
        BilinearDebayerOMP::DebayerBottomLeft(_blueChannel);
        BilinearDebayerOMP::DebayerTopRight(_redChannel);
        break;
    }

    BilinearDebayerOMP::DebayerGreen0();
    BilinearDebayerOMP::DebayerGreen1();
    BilinearDebayerOMP::DemosaicBorders(_blueChannel);
    BilinearDebayerOMP::DemosaicBorders(_greenChannel);
    BilinearDebayerOMP::DemosaicBorders(_redChannel);
}

void BilinearDebayerOMP::DebayerNearest(uint32_t red, uint32_t green0, uint32_t green1, uint32_t blue)
{
    for(uint32_t index = 0; index < _size; index += 2)
    {
        _redChannel[index + green0] = _redChannel[index + red];
        _redChannel[index + green1] = _redChannel[index + red];
        _redChannel[index + blue]   = _redChannel[index + red];

        _greenChannel[index + red]  = _greenChannel[index + green0];
        _greenChannel[index + blue] = _greenChannel[index + green1];

        _blueChannel[index + red]    = _blueChannel[index + blue];
        _blueChannel[index + green0] = _blueChannel[index + blue];
        _blueChannel[index + green1] = _blueChannel[index + blue];

        if ( ((index + 2) % _width) == 0 ) {
            index += _width;
        }
    }
}

void BilinearDebayerOMP::ProcessNearest()
{
    // Nearest Interpolation Processor.
    switch (_pattern)
    {
    case BayerPattern::RGGB:
        DebayerNearest(0, 1, _width, _width + 1);
        break;
    case BayerPattern::BGGR:
        DebayerNearest(_width + 1, 1, _width, 0);
        break;
    case BayerPattern::GRBG:
        DebayerNearest(1, 0, _width + 1, _width);
        break;
    case BayerPattern::GBRG:
        DebayerNearest(_width, 0, _width + 1, 1);
        break;
    }
}

void BilinearDebayerOMP::SetPatternOffsets(BayerPattern pattern)
{
    switch (pattern) {
    case BayerPattern::RGGB:
    case BayerPattern::BGGR:
        _patternOffsets[0] = 1;
        _patternOffsets[1] = 1;
        _patternOffsets[2] = 2;
        _patternOffsets[3] = 2;
        break;
    case BayerPattern::GRBG:
    case BayerPattern::GBRG:
        _patternOffsets[0] = 1;
        _patternOffsets[1] = 2;
        _patternOffsets[2] = 2;
        _patternOffsets[3] = 1;
        break;
    }
}
