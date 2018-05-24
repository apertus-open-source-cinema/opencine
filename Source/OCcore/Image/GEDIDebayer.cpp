// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "GEDIDebayer.h"

// TODO: Add multi-threading.
#include <thread>

#include <Log/Logger.h>

GEDIDebayer::GEDIDebayer(OCImage &image)
{
    _width = image.Width();
    _height = image.Height();
    _size = _width * _height;

    _redChannel = static_cast<uint16_t*>(image.RedChannel());
    _greenChannel = static_cast<uint16_t*>(image.GreenChannel());
    _blueChannel = static_cast<uint16_t*>(image.BlueChannel());

    _pattern = image.GetBayerPattern();
    SetPatternOffsets(_pattern);

    OC_LOG_INFO("\nConsidering width as " + std::to_string(_width) + ":\n" + std::to_string(_patternOffsets[0]) + "\n" + std::to_string(_patternOffsets[1]) + "\n" + std::to_string(_patternOffsets[2]) + "\n" + std::to_string(_patternOffsets[3]) + "\n");
}

GEDIDebayer::~GEDIDebayer()
{
}

void GEDIDebayer::DebayerBottomRight(uint16_t *channel)
{
    for(int index = _patternOffsets[0]; index < _size; index += 2)
    {
        channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
        channel[index + 1] = ( channel[index + _width + 1] + channel[index - _width + 1] ) >> 1;
        channel[index + _width] = ( channel[index + _width - 1] + channel[index + _width + 1] ) >> 1;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void GEDIDebayer::DebayerBottomLeft(uint16_t *channel)
{
    for(int index = _patternOffsets[0]; index < _size; index += 2)
    {
        channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
        channel[index - 1] = ( channel[index + _width - 1] + channel[index - _width - 1] ) >> 1;
        channel[index + _width] = ( channel[index + _width - 1] + channel[index + _width + 1] ) >> 1;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void GEDIDebayer::DebayerGreen()
{
    int hGrad, hValue, vValue, vGrad;
    for(int index = _patternOffsets[1]; index < _size; index += 2)
    {
        hValue = (_greenChannel[index - 1] + _greenChannel[index + 1]) >> 1;
        hGrad = std::abs(_greenChannel[index - 1] - hValue) + std::abs(_greenChannel[index + 1] - hValue);
        vValue = (_greenChannel[index - _width] + _greenChannel[index + _width]) >> 1;
        vGrad = std::abs(_greenChannel[index - _width] - vValue) + std::abs(_greenChannel[index + _width] - vValue);

        if (hGrad <= vGrad)
            _greenChannel[index] = hValue;
        else
            _greenChannel[index] = vValue;

        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
    for(int index = _patternOffsets[2]; index < _size; index += 2)
    {
        hValue = (_greenChannel[index - 1] + _greenChannel[index + 1]) >> 1;
        hGrad = std::abs(_greenChannel[index - 1] - hValue) + std::abs(_greenChannel[index + 1] - hValue);
        vValue = (_greenChannel[index - _width] + _greenChannel[index + _width]) >> 1;
        vGrad = std::abs(_greenChannel[index - _width] - vValue) + std::abs(_greenChannel[index + _width] - vValue);

        if (hGrad <= vGrad)
            _greenChannel[index] = hValue;
        else
            _greenChannel[index] = vValue;

        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void GEDIDebayer::DebayerTopLeft(uint16_t *channel)
{
    for(int index = _patternOffsets[3]; index < _size; index += 2)
    {
        channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
        channel[index - 1] = ( channel[index + _width - 1] + channel[index - _width - 1] ) >> 1;
        channel[index - _width] = ( channel[index - _width - 1] + channel[index - _width + 1] ) >> 1;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void GEDIDebayer::DebayerTopRight(uint16_t *channel)
{
    for(int index = _patternOffsets[3]; index < _size; index += 2)
    {
        channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
        channel[index + 1] = ( channel[index + _width + 1] + channel[index - _width + 1] ) >> 1;
        channel[index - _width] = ( channel[index - _width - 1] + channel[index - _width + 1] ) >> 1;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void GEDIDebayer::DemosaicBorders(uint16_t *channel)
{
    int size = _size - _width;
    for(int index = 0; index < _width; index += 2)
    {
        channel[index] = channel[index + _width];
        channel[index + 1] = channel[index + _width + 1];
        channel[size + index] = channel[size + index - _width];
        channel[size + index + 1] = channel[size + index - _width + 1];
    }
    for(int index = 0; index < _height; index += 2)
    {
        channel[(index * _width)] = channel[(index * _width) + 1];
        channel[(index + 1) * _width] = channel[((index + 1) * _width) + 1];
        channel[((index + 1) * _width) - 1] = channel[((index + 1) * _width) - 2];
        channel[((index + 2) * _width) - 1] = channel[((index + 2) * _width) - 2];
    }
}

void GEDIDebayer::Process()
{
    switch (_pattern) {
    case BayerPattern::RGGB:
        GEDIDebayer::DebayerBottomRight(_redChannel);
        GEDIDebayer::DebayerTopLeft(_blueChannel);
        break;
    case BayerPattern::BGGR:
        GEDIDebayer::DebayerBottomRight(_blueChannel);
        GEDIDebayer::DebayerTopLeft(_redChannel);
        break;
    case BayerPattern::GRBG:
        GEDIDebayer::DebayerBottomLeft(_redChannel);
        GEDIDebayer::DebayerTopRight(_blueChannel);
        break;
    case BayerPattern::GBRG:
        GEDIDebayer::DebayerBottomLeft(_blueChannel);
        GEDIDebayer::DebayerTopRight(_redChannel);
        break;
    default:
        break;
    }
    GEDIDebayer::DebayerGreen();
    GEDIDebayer::DemosaicBorders(_blueChannel);
    GEDIDebayer::DemosaicBorders(_greenChannel);
    GEDIDebayer::DemosaicBorders(_redChannel);
}

void GEDIDebayer::SetPatternOffsets(BayerPattern pattern)
{
    switch (pattern) {
    case BayerPattern::RGGB:
    case BayerPattern::BGGR:
        _patternOffsets[0] = _width + 1;
        _patternOffsets[1] = _width + 1;
        _patternOffsets[2] = (2 * _width) + 2;
        _patternOffsets[3] = (2 * _width) + 2;
        break;
    case BayerPattern::GRBG:
    case BayerPattern::GBRG:
        _patternOffsets[0] = _width + 2;
        _patternOffsets[1] = _width + 2;
        _patternOffsets[2] = (2 * _width) + 1;
        _patternOffsets[3] = (2 * _width) + 1;
        break;
    default:
        break;

    }
}
