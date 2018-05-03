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
}

BilinearDebayer::~BilinearDebayer()
{
}

void BilinearDebayer::ProcessRed()
{
    for(int index = (_width << 1); index < _size; index += 2)
    {
        _redChannel[index] = (_redChannel[index - _width] + _redChannel[index + _width]) >> 1;
        _redChannel[index + 1] = (_redChannel[index - _width] + _redChannel[index - _width + 2] + _redChannel[index + _width] + _redChannel[index + _width + 2]) >> 2;
        _redChannel[index + _width + 1] = (_redChannel[index + _width] + _redChannel[index + _width + 2]) >> 1;
        if ((index + 4) % _width == 0)
            index += _width + 4;
    }
}

void BilinearDebayer::ProcessGreen()
{
    for(int index = (_width << 1); index < _size; index += 2)
    {
        _greenChannel[index + 1] = (_greenChannel[index - _width + 1] + _greenChannel[index] + _greenChannel[index + 2] + _greenChannel[index + _width + 1]) >> 2;
        _greenChannel[index + _width] = (_greenChannel[index] + _greenChannel[index + _width - 1] + _greenChannel[index + _width + 1] + _greenChannel[index + 2 * _width]) >> 2;
        if ((index + 4) % _width == 0)
            index += _width + 4;
    }
}

void BilinearDebayer::ProcessBlue()
{
    for(int index = (_width << 1); index < _size; index += 2)
    {
        _blueChannel[index] = (_blueChannel[index - 1] + _blueChannel[index + 1]) >> 1;
        _blueChannel[index + _width] = (_blueChannel[index - 1] + _blueChannel[index + 1] + _blueChannel[index + 2 * _width - 1] + _blueChannel[index + 2 * _width + 1]) >> 2;
        _blueChannel[index + _width + 1] = (_blueChannel[index + 1] + _blueChannel[index + 2 * _width + 1]) >> 1;
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
