// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef GEDIDEBAYER_H
#define GEDIDEBAYER_H

#include "IFrameProcessor.h"
#include "OCImage.h"

using namespace OC::DataProvider;

class GEDIDebayer
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
    GEDIDebayer(OCImage& image);

    ~GEDIDebayer();

    // Debayers for each color channel.
    void DebayerBottomRight(uint16_t *channel);
    void DebayerBottomLeft(uint16_t *channel);
    void DebayerGreen();
    void DebayerTopRight(uint16_t *channel);
    void DebayerTopLeft(uint16_t *channel);

    // Debayers Borders.
    void DemosaicBorders(uint16_t *channel);

    // Main Processor.
    void Process();

    // Sets correct Pattern Offset.
    void SetPatternOffsets(BayerPattern pattern);
};

#endif //GEDIDEBAYER_H
