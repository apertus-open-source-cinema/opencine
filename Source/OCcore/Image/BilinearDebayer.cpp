// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "BilinearDebayer.h"

// TODO: Add multi-threading.
#include <thread>

#include <Log/Logger.h>

BilinearDebayer::BilinearDebayer(OCImage &image)
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

BilinearDebayer::~BilinearDebayer()
{
}

void BilinearDebayer::ProcessBottomRight(uint16_t *channel)
{
    // TODO: Demosaic borders.
    for(int index = _patternOffsets[0]; index < _size - _width; index += 2)
    {
        channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
        channel[index + 1] = ( channel[index + _width + 1] + channel[index - _width + 1] ) >> 1;
        channel[index + _width] = ( channel[index + _width - 1] + channel[index + _width + 1] ) >> 1;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void BilinearDebayer::ProcessBottomLeft(uint16_t *channel)
{
    // TODO: Demosaic borders.
    for(int index = _patternOffsets[0]; index < _size - _width; index += 2)
    {
        channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
        channel[index - 1] = ( channel[index + _width - 1] + channel[index - _width - 1] ) >> 1;
        channel[index + _width] = ( channel[index + _width - 1] + channel[index + _width + 1] ) >> 1;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void BilinearDebayer::ProcessGreen()
{
    // TODO: Demosaic borders.
    for(int index = _patternOffsets[1]; index < _size - _width; index += 2)
    {
        _greenChannel[index] = ( _greenChannel[index - _width] + _greenChannel[index - 1] + _greenChannel[index + 1] + _greenChannel[index + _width] ) >> 2;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
    for(int index = _patternOffsets[2]; index < _size; index += 2)
    {
         _greenChannel[index] = ( _greenChannel[index - _width] + _greenChannel[index - 1] + _greenChannel[index + 1] + _greenChannel[index + _width] ) >> 2;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void BilinearDebayer::ProcessTopLeft(uint16_t *channel)
{
    // TODO: Demosaic borders.
    for(int index = _patternOffsets[3]; index < _size; index += 2)
    {
        channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
        channel[index - 1] = ( channel[index + _width - 1] + channel[index - _width - 1] ) >> 1;
        channel[index - _width] = ( channel[index - _width - 1] + channel[index - _width + 1] ) >> 1;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void BilinearDebayer::ProcessTopRight(uint16_t *channel)
{
    // TODO: Demosaic borders.
    for(int index = _patternOffsets[3]; index < _size; index += 2)
    {
        channel[index] = ( channel[index - _width - 1] + channel[index - _width + 1] + channel[index + _width - 1] + channel[index + _width + 1] ) >> 2;
        channel[index + 1] = ( channel[index + _width + 1] + channel[index - _width + 1] ) >> 1;
        channel[index - _width] = ( channel[index - _width - 1] + channel[index - _width + 1] ) >> 1;
        if ((index + 3) % _width <= 1)
            index += _width + 2;
    }
}

void BilinearDebayer::Process()
{
    switch (_pattern) {
    case BayerPattern::RGGB:
        BilinearDebayer::ProcessBottomRight(_redChannel);
        BilinearDebayer::ProcessGreen();
        BilinearDebayer::ProcessTopLeft(_blueChannel);
        break;
    case BayerPattern::BGGR:
        BilinearDebayer::ProcessBottomRight(_blueChannel);
        BilinearDebayer::ProcessGreen();
        BilinearDebayer::ProcessTopLeft(_redChannel);
        break;
    case BayerPattern::GRBG:
        BilinearDebayer::ProcessBottomLeft(_redChannel);
        BilinearDebayer::ProcessGreen();
        BilinearDebayer::ProcessTopRight(_blueChannel);
        break;
    case BayerPattern::GBRG:
        BilinearDebayer::ProcessBottomLeft(_blueChannel);
        BilinearDebayer::ProcessGreen();
        BilinearDebayer::ProcessTopRight(_redChannel);
        break;
    default:
        break;
    }
}

void BilinearDebayer::SetPatternOffsets(BayerPattern pattern)
{
    switch (pattern) {
    case BayerPattern::RGGB:
        _patternOffsets[0] = _width + 1;
        _patternOffsets[1] = _width + 1;
        _patternOffsets[2] = (2 * _width) + 2;
        _patternOffsets[3] = (2 * _width) + 2;
        break;
    case BayerPattern::BGGR:
        _patternOffsets[0] = (2 * _width) + 2;
        _patternOffsets[1] = _width + 1;
        _patternOffsets[2] = (2 * _width) + 2;
        _patternOffsets[3] = _width + 1;
        break;
    case BayerPattern::GRBG:
        _patternOffsets[0] = _width + 2;
        _patternOffsets[1] = _width + 2;
        _patternOffsets[2] = (2 * _width) + 1;
        _patternOffsets[3] = (2 * _width) + 1;
        break;
    case BayerPattern::GBRG:
        _patternOffsets[0] = (2 * _width) + 1;
        _patternOffsets[1] = _width + 2;
        _patternOffsets[2] = (2 * _width) + 1;
        _patternOffsets[3] = _width + 2;
        break;
    default:
        _patternOffsets[0] = _width + 1;
        _patternOffsets[1] = _width + 1;
        _patternOffsets[2] = (2 * _width) + 2;
        _patternOffsets[3] = (2 * _width) + 2;
        break;

    }
}
