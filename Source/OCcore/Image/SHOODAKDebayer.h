// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef SHOODAKDEBAYER_H
#define SHOODAKDEBAYER_H

#include "IFrameProcessor.h"
#include "OCImage.h"
#include "IDebayerProcessor.h"

#include "OCcore_export.h"

using namespace OC::DataProvider;

class SHOODAKDebayer : public IDebayerProcessor
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

    BayerPattern _pattern;

    // Pattern Offsets. The indexes follow the order: Red/Blue, Green0, Green1, Blue/Red.
    uint32_t _patternOffsets[4];

public:
    SHOODAKDebayer();
    SHOODAKDebayer(OCImage& image);

    ~SHOODAKDebayer();

    // Debayers for each color channel.
    void DebayerRed(int hOffset, int vOffset);
    void DebayerGreen(int hOffset, int vOffset);
    void DebayerBlue(int hOffset, int vOffset);

    // Main Processor.
    void Process();
    void Process(OCImage& image);

    // Sets correct Pattern Offset.
    void SetPatternOffsets(BayerPattern pattern);
};

#endif //SHOODAKDEBAYER_H
