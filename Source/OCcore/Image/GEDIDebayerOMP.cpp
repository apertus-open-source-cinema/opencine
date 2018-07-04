// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "GEDIDebayerOMP.h"

// TODO: Add multi-threading.
#include <omp.h>

#include <Log/Logger.h>

GEDIDebayerOMP::GEDIDebayerOMP()
{
    // TODO (BAndiT1983): Add implementation
}

GEDIDebayerOMP::GEDIDebayerOMP(OCImage &image)
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

GEDIDebayerOMP::~GEDIDebayerOMP()
{
}

void GEDIDebayerOMP::DebayerBottomRight(uint16_t *channel)
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

void GEDIDebayerOMP::DebayerBottomLeft(uint16_t *channel)
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

void GEDIDebayerOMP::DebayerGreen0()
{
    uint32_t hGrad, vGrad, index;
    #pragma omp parallel for private(hGrad, vGrad) collapse(2)
    for(uint32_t row = _patternOffsets[0]; row < _height; row += 2)
    {
        for(uint32_t col = _patternOffsets[1]; col < _width; col += 2)
        {
            index = (row * _width) + col;

            hGrad = std::abs(_greenChannel[index - 1] - _greenChannel[index + 1]);
            vGrad = std::abs(_greenChannel[index - _width] - _greenChannel[index + _width]);

            if (hGrad <= vGrad)
            {
                _greenChannel[index] = (_greenChannel[index - 1] + _greenChannel[index + 1]) >> 1;
            }
            else
            {
                _greenChannel[index] = (_greenChannel[index - _width] + _greenChannel[index + _width]) >> 1;
            }
        }
    }
}

void GEDIDebayerOMP::DebayerGreen1()
{
    uint32_t hGrad, vGrad, index;
    #pragma omp parallel for private(hGrad, vGrad) collapse(2)
    for(uint32_t row = _patternOffsets[2]; row < _height; row += 2)
    {
        for(uint32_t col = _patternOffsets[3]; col < _width; col += 2)
        {
            index = (row * _width) + col;

            hGrad = std::abs(_greenChannel[index - 1] - _greenChannel[index + 1]);
            vGrad = std::abs(_greenChannel[index - _width] - _greenChannel[index + _width]);

            if (hGrad <= vGrad)
            {
                _greenChannel[index] = (_greenChannel[index - 1] + _greenChannel[index + 1]) >> 1;
            }
            else
            {
                _greenChannel[index] = (_greenChannel[index - _width] + _greenChannel[index + _width]) >> 1;
            }
        }
    }
}

void GEDIDebayerOMP::DebayerTopLeft(uint16_t *channel)
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

void GEDIDebayerOMP::DebayerTopRight(uint16_t *channel)
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

void GEDIDebayerOMP::DemosaicBorders(uint16_t *channel)
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

void GEDIDebayerOMP::Process()
{
    switch (_pattern) {
    case BayerPattern::RGGB:
        GEDIDebayerOMP::DebayerBottomRight(_redChannel);
        GEDIDebayerOMP::DebayerTopLeft(_blueChannel);
        break;
    case BayerPattern::BGGR:
        GEDIDebayerOMP::DebayerBottomRight(_blueChannel);
        GEDIDebayerOMP::DebayerTopLeft(_redChannel);
        break;
    case BayerPattern::GRBG:
        GEDIDebayerOMP::DebayerBottomLeft(_redChannel);
        GEDIDebayerOMP::DebayerTopRight(_blueChannel);
        break;
    case BayerPattern::GBRG:
        GEDIDebayerOMP::DebayerBottomLeft(_blueChannel);
        GEDIDebayerOMP::DebayerTopRight(_redChannel);
        break;
    }
    GEDIDebayerOMP::DebayerGreen0();
    GEDIDebayerOMP::DebayerGreen1();
    GEDIDebayerOMP::DemosaicBorders(_blueChannel);
    GEDIDebayerOMP::DemosaicBorders(_greenChannel);
    GEDIDebayerOMP::DemosaicBorders(_redChannel);
}

void GEDIDebayerOMP::Process(OCImage &image)
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

void GEDIDebayerOMP::SetPatternOffsets(BayerPattern pattern)
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
