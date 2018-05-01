// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef DEBAYERBILINEAR_H
#define DEBAYERBILINEAR_H

#include "IFrameProcessor.h"
#include "OCImage.h"

using namespace OC::DataProvider;

class DebayerBilinear
{
private:
    // Color Channels.
    uint16_t* _redChannel;
    uint16_t* _greenChannel;
    uint16_t* _blueChannel;

    // Image Dimensions.
    uint32_t _width;
    uint32_t _height;
    uint32_t _size;

    // TODO
    // _patternOffsets

public:
    DebayerBilinear(OCImage& image);

    ~DebayerBilinear();

    // Processors for each color channel.
    void ProcessRed();
    void ProcessBlue();
    void ProcessGreen();

    // Main Processor.
    void Process();

};

#endif //DEBAYERBILINEAR_H
