// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef BILINEARDEBAYER_H
#define BILINEARDEBAYER_H

#include "IDebayerProcessor.h"
#include "IFrameProcessor.h"
#include "OCImage.h"

using namespace OC::DataProvider;

class BilinearDebayer : public IDebayerProcessor
{
private:
    // Color Channels.
    uint16_t *_redChannel;
    uint16_t *_greenChannel;
    uint16_t *_blueChannel;

    // Image Dimensions.
    uint32_t _width;
    uint32_t _height;
    uint32_t _size;

    OC::Image::BayerPattern _pattern;

    // Pattern Offsets. The indexes follow the order: Red/Blue, Green0, Green1, Blue/Red.
    uint32_t _patternOffsets[4];

public:
    BilinearDebayer();

    BilinearDebayer(OC::Image::OCImage &image);

    ~BilinearDebayer();

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

    // TODO (BAndiT1983): Evaluate if this method should be pulled up to the interface
    void Process(OC::Image::OCImage &image);

    // Debayer for Nearest Interpolation.
    void DebayerNearest(uint32_t red, uint32_t green0, uint32_t green1, uint32_t blue);

    // Processor for Nearest Interpolation.
    void ProcessNearest();

    // Sets correct Pattern Offset.
    void SetPatternOffsets(OC::Image::BayerPattern pattern);
};

#endif // BilinearDebayer_H
