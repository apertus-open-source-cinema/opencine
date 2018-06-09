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

    OC_LOG_INFO("\nConsidering width as " + std::to_string(_width) + ":\n" + std::to_string(_patternOffsets[0]) + "\n" + std::to_string(_patternOffsets[1]) + "\n" + std::to_string(_patternOffsets[2]) + "\n" + std::to_string(_patternOffsets[3]) + "\n");
}

SHOODAKDebayer::~SHOODAKDebayer()
{
}

void SHOODAKDebayer::DebayerRed(int hOffset, int vOffset)
{
    for(int index = 0; index < _size; index += 2)
    {
        _redChannel[index]              = _redChannel[index + _patternOffsets[0]];
        _redChannel[index + 1]          = _redChannel[index + _patternOffsets[0] + hOffset];
        _redChannel[index + _width]     = _redChannel[index + vOffset * _width + _patternOffsets[0]];
        _redChannel[index + _width + 1] = _redChannel[index + vOffset * _width + _patternOffsets[0] + hOffset];
        if ((index + 2) % _width == 0)
            index += _width;
    }
}

void SHOODAKDebayer::DebayerGreen(int hOffset, int vOffset)
{
    std::mt19937 gen(123456);
    std::uniform_int_distribution<> dis(1, 2);

    double greenRatio;
    int greenInterpolation, randomOffset;

    for(int index = 0; index < _size; index += 2)
    {
        greenRatio = ((double) _greenChannel[index + _patternOffsets[1]]) / ( (double) _greenChannel[index + _patternOffsets[2]]);
//        OC_LOG_INFO("\ngreenRatio " + std::to_string(greenRatio));

        if (greenRatio > 1.25 || greenRatio < 0.8)
        {
            greenInterpolation = (_greenChannel[index + _patternOffsets[1]] + _greenChannel[index + _patternOffsets[2]]) >> 1;
            _greenChannel[index]                = greenInterpolation;
            _greenChannel[index + 1]            = greenInterpolation;
            _greenChannel[index + _width]       = greenInterpolation;
            _greenChannel[index + _width + 1]   = greenInterpolation;

//            _greenChannel[index]                = 255;
//            _greenChannel[index + 1]            = 255;
//            _greenChannel[index + _width]       = 255;
//            _greenChannel[index + _width + 1]   = 255;
        }
        else
        {
            _greenChannel[index]                = _greenChannel[index + _patternOffsets[dis(gen)]];

            if (dis(gen) == 1)
                randomOffset = index + hOffset + _patternOffsets[1];
            else
                randomOffset = index + vOffset + _patternOffsets[2];
            _greenChannel[index + 1]            = _greenChannel[randomOffset];

            if (dis(gen) == 1)
                randomOffset = index + vOffset * _width + _patternOffsets[1];
            else
                randomOffset = index + hOffset * _width + _patternOffsets[2];
            _greenChannel[index + _width]       = _greenChannel[randomOffset];

            if (dis(gen) == 1)
                randomOffset = index + hOffset + vOffset * _width + _patternOffsets[1];
            else
                randomOffset = index + vOffset + hOffset * _width + _patternOffsets[2];
            _greenChannel[index + _width + 1]   = _greenChannel[randomOffset];

//            _greenChannel[index]                =  0;
//            _greenChannel[index + 1]            = 0;
//            _greenChannel[index + _width]       =  0;
//            _greenChannel[index + _width + 1]   =  0;
        }

        if ((index + 2) % _width == 0)
            index += _width + 2;
    }
}

void SHOODAKDebayer::DebayerBlue(int hOffset, int vOffset)
{
    for(int index = 0; index < _size; index += 2)
    {
        _blueChannel[index]              = _blueChannel[index + _patternOffsets[3]];
        _blueChannel[index + 1]          = _blueChannel[index + _patternOffsets[3] + hOffset];
        _blueChannel[index + _width]     = _blueChannel[index + vOffset * _width + _patternOffsets[3]];
        _blueChannel[index + _width + 1] = _blueChannel[index + vOffset * _width + _patternOffsets[3] + hOffset];
        if ((index + 2) % _width == 0)
            index += _width;
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
