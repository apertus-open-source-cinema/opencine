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

    SetPatternOffsets(image.GetBayerPattern());

    OC_LOG_INFO("\nConsidering width as " + std::to_string(_width) + ":\n" + std::to_string(_patternOffsets[0]) + "\n" + std::to_string(_patternOffsets[1]) + "\n" + std::to_string(_patternOffsets[2]) + "\n" + std::to_string(_patternOffsets[3]) + "\n");
}

BilinearDebayer::~BilinearDebayer()
{
}

void BilinearDebayer::ProcessRed()
{
    for(int index = (_width << 1); index < _size; index += 2)
    {
        // TODO
        if ((index + 4) % _width == 0)
            index += _width + 4;
    }
}

void BilinearDebayer::ProcessGreen()
{
    for(int index = (_width << 1); index < _size; index += 2)
    {
        // TODO
        if ((index + 4) % _width == 0)
            index += _width + 4;
    }
}

void BilinearDebayer::ProcessBlue()
{
    for(int index = (_width << 1); index < _size; index += 2)
    {
        // TODO
        if ((index + 4) % _width == 0)
            index += _width + 4;
    }
}

void BilinearDebayer::Process()
{
    BilinearDebayer::ProcessRed();
    BilinearDebayer::ProcessGreen();
    BilinearDebayer::ProcessBlue();
}

void BilinearDebayer::SetPatternOffsets(BayerPattern pattern)
{
    switch (pattern) {
    case BayerPattern::RGGB:
        _patternOffsets[0] = 0;
        _patternOffsets[1] = 1;
        _patternOffsets[2] = _width;
        _patternOffsets[3] = _width + 1;
        break;
    case BayerPattern::BGGR:
        _patternOffsets[0] = _width + 1;
        _patternOffsets[1] = 1;
        _patternOffsets[2] = _width;
        _patternOffsets[3] = 0;
        break;
    case BayerPattern::GRBG:
        _patternOffsets[0] = 1;
        _patternOffsets[1] = 0;
        _patternOffsets[2] = _width + 1;
        _patternOffsets[3] = _width;
        break;
    case BayerPattern::GBRG:
        _patternOffsets[0] = _width;
        _patternOffsets[1] = 0;
        _patternOffsets[2] = _width + 1;
        _patternOffsets[3] = 1;
        break;
    default:
        _patternOffsets[0] = _width;
        _patternOffsets[1] = 0;
        _patternOffsets[2] = _width + 1;
        _patternOffsets[3] = 1;
        break;

    }
}
