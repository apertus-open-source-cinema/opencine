// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef BAYERPROCESSOR_H
#define BAYERPROCESSOR_H

#include "IFrameProcessor.h"
#include "OCImage.h"

using namespace OC::DataProvider;

class BayerFramePreProcessor : public OC::DataProvider::IFrameProcessor
{
    uint8_t* _data;
    uint16_t* _outputData;
    unsigned int _size;

    BayerPattern _pattern = BayerPattern::RGGB;

    uint16_t* _dataUL; //upper-left data
    uint16_t* _dataUR; //upper-right data
    uint16_t* _dataLL; //lower-left data
    uint16_t* _dataLR; //lower-right data

    uint16_t* _dataRed;
    uint16_t* _dataGreen;
    uint16_t* _dataBlue;

    unsigned int _width;
    unsigned int _height;

    ImageFormat _imageFormat;

    void MapPatternToData();

    void ExtractOddRows() const;

    void ExtractEvenRows() const;

public:
    BayerFramePreProcessor();

    ~BayerFramePreProcessor();

    void SetData(uint8_t* data, OCImage& image, ImageFormat imageFormat) override;
    void SetData(uint16_t* imageData, OCImage& image) override;

    void Process() override;

    unsigned short* GetDataRed() override;

    unsigned short* GetDataGreen() override;

    unsigned short* GetDataBlue() override;

    unsigned short* _linearizationTable = nullptr;
    unsigned int _linearizationLength = 0;

    void SetLinearizationData(unsigned short* linearizationTable, unsigned int linearizationLength);
};

#endif // IFRAMEPROCESSOR_H

