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

    uint16_t* dataUL; //upper-left data
    uint16_t* dataUR; //upper-right data
    uint16_t* dataLL; //lower-left data
    uint16_t* dataLR; //lower-right data

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

    //void SetData(unsigned char &data, int width, int height, OC::DataProvider::SourceFormat sourceFormat);

    //virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, OC::DataProvider::SourceFormat sourceFormat) override;

    //virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, OC::DataProvider::SourceFormat sourceFormat, BayerPattern pattern);

    void SetData(uint8_t* data, OCImage& image, ImageFormat imageFormat) override;

    void Process() override;

    void Convert12To16Bit() const;
    void Convert14To16Bit() const;

    /*void Convert14To16Bit()
    {
    }*/

    unsigned short* GetDataRed() override;

    unsigned short* GetDataGreen() override;

    unsigned short* GetDataBlue() override;

    unsigned short* _linearizationTable = nullptr;
    unsigned int _linearizationLength = 0;

    void SetLinearizationData(unsigned short* linearizationTable, unsigned int linearizationLength);
};

#endif // IFRAMEPROCESSOR_H

