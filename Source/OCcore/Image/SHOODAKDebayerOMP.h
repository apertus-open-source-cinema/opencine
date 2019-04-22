// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef SHOODAKDEBAYEROMP_H
#define SHOODAKDEBAYEROMP_H

#include "IDebayerProcessor.h"
#include "IFrameProcessor.h"
#include "OCImage.h"

#include "OCcore_export.h"

class SHOODAKDebayerOMP : public IDebayerProcessor
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

    OC::Image::BayerPattern _pattern;

    // Pattern Offsets. The indexes follow the order: Red/Blue, Green0, Green1, Blue/Red.
    uint32_t _patternOffsets[4];

public:
    SHOODAKDebayerOMP();
    SHOODAKDebayerOMP(OC::Image::OCImage& image);

    ~SHOODAKDebayerOMP();

    // Debayers for each color channel.
    void DebayerRed(uint32_t hOffset, uint32_t vOffset);
    void DebayerGreen(uint32_t hOffset, uint32_t vOffset);
    void DebayerBlue(uint32_t hOffset, uint32_t vOffset);

    // Debayers Borders.
    void DemosaicBorders(uint16_t* channel);

    // Main Processor.
    void Process();
    void Process(OC::Image::OCImage& image);

    // Sets correct Pattern Offset.
    void SetPatternOffsets(OC::Image::BayerPattern pattern);
};

#endif // SHOODAKDEBAYEROMP_H
