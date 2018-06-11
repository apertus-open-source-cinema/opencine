// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "SHOODAKDebayer.h"

#include <random>
#include <thread>

#include <Log/Logger.h>

SHOODAKDebayer::SHOODAKDebayer()
{
    // TODO (BAndiT1983): Add implementation
}

SHOODAKDebayer::SHOODAKDebayer(OCImage &image)
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

SHOODAKDebayer::~SHOODAKDebayer()
{
}

void SHOODAKDebayer::DebayerRed(int hOffset, int vOffset)
{
    int rValue0, rValue1, rValue2, rValue3;
    for(int index = 0; index < _size; index += 2)
    {
        rValue0 = _redChannel[index + _patternOffsets[0]];
        rValue1 = _redChannel[index + _patternOffsets[0] + hOffset];
        rValue2 = _redChannel[index + vOffset * _width + _patternOffsets[0]];
        rValue3 = _redChannel[index + vOffset * _width + _patternOffsets[0] + hOffset];

        _redChannel[index]              = rValue0;
        _redChannel[index + 1]          = rValue1;
        _redChannel[index + _width]     = rValue2;
        _redChannel[index + _width + 1] = rValue3;

        if ((index + 2) % _width == 0)
            index += _width;
    }
}

void SHOODAKDebayer::DebayerGreen(int hOffset, int vOffset)
{
    std::mt19937 gen(123456);
    std::uniform_int_distribution<> dis(1, 2);

    double greenRatio;
    int gValue0, gValue1, gValue2, gValue3;
    int randomOffset;

    for(int index = 0; index < _size; index += 2)
    {
        greenRatio = ((double) _greenChannel[index + _patternOffsets[1]]) / ( (double) _greenChannel[index + _patternOffsets[2]]);

        if (greenRatio > 1.176 || greenRatio < 0.85)
        {
            gValue0 = (_greenChannel[index + _patternOffsets[1]] +                          _greenChannel[index + _patternOffsets[2]])           >> 1;
            gValue1 = (_greenChannel[index + _patternOffsets[1] + vOffset] +                _greenChannel[index + _patternOffsets[2] + hOffset]) >> 1;
            gValue2 = (_greenChannel[index + _patternOffsets[1] + 2 * _width] +             _greenChannel[index + _patternOffsets[2]])           >> 1;
            gValue3 = (_greenChannel[index + _patternOffsets[1] + 2 * _width + vOffset] +   _greenChannel[index + _patternOffsets[2] + hOffset]) >> 1;

            _greenChannel[index]              = gValue0;
            _greenChannel[index + 1]          = gValue1;
            _greenChannel[index + _width]     = gValue2;
            _greenChannel[index + _width + 1] = gValue3;
        }
        else
        {
            if (dis(gen) == 1)
                gValue1 = _greenChannel[index + _patternOffsets[1] + vOffset];
            else
                gValue1 = _greenChannel[index + _patternOffsets[2] + hOffset];

            if (dis(gen) == 1)
                gValue2 = _greenChannel[index + _patternOffsets[1] + 2 * _width];
            else
                gValue2 = _greenChannel[index + _patternOffsets[2]];

            if (dis(gen) == 1)
                gValue3 = _greenChannel[index + _patternOffsets[1] + 2 * _width + vOffset];
            else
                gValue3 = _greenChannel[index + _patternOffsets[2] + hOffset];

            _greenChannel[index]              = _greenChannel[index + _patternOffsets[dis(gen)]];
            _greenChannel[index + 1]          = gValue1;
            _greenChannel[index + _width]     = gValue2;
            _greenChannel[index + _width + 1] = gValue3;
        }

        if ((index + 2) % _width == 0)
            index += _width;
    }
}

void SHOODAKDebayer::DebayerBlue(int hOffset, int vOffset)
{
    int bValue0, bValue1, bValue2, bValue3;
    for(int index = 0; index < _size; index += 2)
    {
        bValue0 = _blueChannel[index + _patternOffsets[3]];
        bValue1 = _blueChannel[index + _patternOffsets[3] + hOffset];
        bValue2 = _blueChannel[index + vOffset * _width + _patternOffsets[3]];
        bValue3 = _blueChannel[index + vOffset * _width + _patternOffsets[3] + hOffset];

        _blueChannel[index]              = bValue0;
        _blueChannel[index + 1]          = bValue1;
        _blueChannel[index + _width]     = bValue2;
        _blueChannel[index + _width + 1] = bValue3;

        if ((index + 2) % _width == 0)
            index += _width;
    }
}

void SHOODAKDebayer::DemosaicBorders(uint16_t *channel)
{
    int size = _size - _width;
    for(int index = 0; index < _width; index += 2)
    {
        channel[size + index] = channel[size + index - _width];
        channel[size + index + 1] = channel[size + index - _width + 1];
    }
    for(int index = 0; index < _height; index += 2)
    {
        channel[((index + 1) * _width) - 1] = channel[((index + 1) * _width) - 2];
        channel[((index + 2) * _width) - 1] = channel[((index + 2) * _width) - 2];
    }
}

void SHOODAKDebayer::Process()
{
    switch (_pattern) {
    case BayerPattern::RGGB:
        DebayerRed(2, 2);
        DebayerGreen(2, 0);
        DebayerBlue(0, 0);
        break;
    case BayerPattern::BGGR:
        DebayerRed(0, 0);
        DebayerGreen(2, 0);
        DebayerBlue(2, 2);
        break;
    case BayerPattern::GRBG:
        DebayerRed(0, 2);
        DebayerGreen(0, 2);
        DebayerBlue(2, 0);
        break;
    case BayerPattern::GBRG:
        DebayerRed(2, 0);
        DebayerGreen(0, 2);
        DebayerBlue(0, 2);
        break;
    default:
        break;
    }

    DemosaicBorders(_redChannel);
    DemosaicBorders(_greenChannel);
    DemosaicBorders(_blueChannel);
}

void SHOODAKDebayer::Process(OCImage &image)
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

    Process();
}

void SHOODAKDebayer::SetPatternOffsets(BayerPattern pattern)
{
    // TODO: Study Pattern offsets approach.
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
        break;

    }
}
