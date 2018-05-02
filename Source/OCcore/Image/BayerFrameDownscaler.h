// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef BAYERPROCESSOR_H
#define BAYERPROCESSOR_H

#include "IFrameProcessor.h"
#include "OCImage.h"

using namespace OC::DataProvider;

class BayerFrameDownscaler : public OC::DataProvider::IFrameProcessor
{
    uint8_t* _data;
    uint16_t* _outputData;
    unsigned int _size;

    BayerPattern _pattern = BayerPattern::RGGB;

    uint16_t* _dataRed;
    uint16_t* _dataGreen;
    uint16_t* _dataBlue;

    unsigned int _width;
    unsigned int _height;

    ImageFormat _imageFormat;

    void Extract(int jump) const;

public:
    BayerFrameDownscaler();

    ~BayerFrameDownscaler();

    void SetData(uint8_t* data, OCImage& image, ImageFormat imageFormat) override;

    void Process() override;

    unsigned short* GetDataRed() override;

    unsigned short* GetDataGreen() override;

    unsigned short* GetDataBlue() override;
};

#endif // IFRAMEPROCESSOR_H

