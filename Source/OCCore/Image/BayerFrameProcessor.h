#ifndef BAYERPROCESSOR_H
#define BAYERPROCESSOR_H

#include <thread>

#include "IFrameProcessor.h"

enum class BayerPattern
{
    RGGB,
    BGGR,
    GRBG,
    GBRG
};

class BayerFramePreProcessor : public OC::DataProvider::IFrameProcessor
{
    unsigned char* _data;
    unsigned short* _outputData;
    unsigned int _size;

    BayerPattern _pattern = BayerPattern::RGGB;

    unsigned short* dataUL; //upper-left data
    unsigned short* dataUR; //upper-right data
    unsigned short* dataLL; //lower-left data
    unsigned short* dataLR; //lower-right data

    unsigned short* _dataRed;
    unsigned short* _dataGreen;
    unsigned short* _dataBlue;

    unsigned int _width;
    unsigned int _height;

    void MapPatternToData()
    {
        switch(_pattern)
        {
        case BayerPattern::RGGB:
            dataUL = _dataRed;
            dataUR = _dataGreen;
            dataLL = _dataGreen;
            dataLR = _dataBlue;
            break;
        case BayerPattern::BGGR:
            dataUL = _dataBlue;
            dataUR = _dataGreen;
            dataLL = _dataGreen;
            dataLR = _dataRed;
            break;
        case BayerPattern::GRBG:
            dataUL = _dataGreen;
            dataUR = _dataRed;
            dataLL = _dataBlue;
            dataLR = _dataGreen;
            break;
        case BayerPattern::GBRG:
            dataUL = _dataGreen;
            dataUR = _dataBlue;
            dataLL = _dataRed;
            dataLR = _dataGreen;
            break;
        }
    }

    void ExtractRedGreen()
    {
        unsigned int rowIndex = 0;
        unsigned int columnIndex = 0;

        //        for(rowIndex = 0; rowIndex <= 3072; rowIndex += 2)
        //        {
        //            for(columnIndex = 0; columnIndex <= 4096; columnIndex+=2)
        //            {
        //                _dataGreen[rowIndex * 4096 + columnIndex + 1] = _outputData[rowIndex * 4096 + columnIndex + 1];
        //                _dataGreen[rowIndex * 4096 + columnIndex] = _outputData[rowIndex * 4096 + columnIndex + 1];

        //                _dataRed[rowIndex * 4096 + columnIndex] = _outputData[rowIndex * 4096 + columnIndex];
        //                _dataRed[rowIndex * 4096 + columnIndex + 1] = _outputData[rowIndex * 4096 + columnIndex];

        //                if(columnIndex == 4095)
        //                {
        //                    memcpy((unsigned short*)&_dataRed[(rowIndex + 1) * 4096], (unsigned short*)&_dataRed[(rowIndex) * 4096], 4096 * sizeof(unsigned short));
        //                }

        //            }
        //        }

        for(rowIndex = 0; rowIndex < _height; rowIndex += 2)
        {
            for(columnIndex = 0; columnIndex < _width; columnIndex++)
            {
                if(columnIndex % 2)
                {
                    dataUR[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
                    //_dataGreen[rowIndex * _width + columnIndex + 1] = _outputData[rowIndex * _width + columnIndex + 1];
                }
                else
                {
                    dataUL[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
                    //_dataRed[rowIndex * _width + columnIndex + 1] = _outputData[rowIndex * _width + columnIndex + 1];
                }
            }
        }
    }

    void ExtractGreenBlue()
    {
        unsigned int rowIndex = 1;
        unsigned int columnIndex = 0;

        //        for(rowIndex = 1; rowIndex < 3072; rowIndex += 2)
        //        {
        //            for(columnIndex = 0; columnIndex < 4096; columnIndex += 2)
        //            {
        //                _dataBlue[rowIndex * 4096 + columnIndex + 1] = _outputData[rowIndex * 4096 + columnIndex + 1];
        //                _dataBlue[rowIndex * 4096 + columnIndex] = _outputData[rowIndex * 4096 + columnIndex + 1];

        //                if(columnIndex == 4096)
        //                {
        //                    memcpy((unsigned short*)&_dataBlue[(rowIndex - 1) * 4096], (unsigned short*)&_dataBlue[rowIndex * 4096], 4096 * sizeof(unsigned short));
        //                }

        //                _dataGreen[rowIndex * 4096 + columnIndex] = _outputData[rowIndex * 4096 + columnIndex];
        //                _dataGreen[rowIndex * 4096 + columnIndex + 1] = _outputData[rowIndex * 4096 + columnIndex + 1];
        //            }
        //        }

        for(rowIndex = 1; rowIndex < _height; rowIndex += 2)
        {
            for(columnIndex = 0; columnIndex < _width; columnIndex++)
            {
                if(columnIndex % 2)
                {
                    dataLR[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
                    //_dataBlue[rowIndex * _width + columnIndex + 1] = _outputData[rowIndex * _width + columnIndex + 1];
                }
                else
                {
                    dataLL[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
                    //_dataGreen[rowIndex * _width + columnIndex + 1] = _outputData[rowIndex * _width + columnIndex + 1];
                }
            }
        }
    }

public:
    BayerFramePreProcessor()
    {

    }

    ~BayerFramePreProcessor()
    {
        delete[] _dataRed;
        delete[] _dataGreen;
        delete[] _dataBlue;

        delete[] _outputData;
    }

    virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, OC::DataProvider::SourceFormat sourceFormat) override
    {
        _data = &data;

        _width = width;
        _height = height;

        _size = _width * _height;

        _outputData = new unsigned short[_size];

        _dataRed = new unsigned short[_size];
        _dataGreen = new unsigned short[_size];
        _dataBlue = new unsigned short[_size];

        MapPatternToData();
    }

    virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, OC::DataProvider::SourceFormat sourceFormat, BayerPattern pattern)
    {
        _data = &data;

        _width = width;
        _height = height;

        _size = _width * _height;

        _outputData = new unsigned short[_size];

        _dataRed = new unsigned short[_size];
        _dataGreen = new unsigned short[_size];
        _dataBlue = new unsigned short[_size];

        _pattern = pattern;

        MapPatternToData();
    }

    void Process()
    {
        Convert12To16Bit();

        std::thread t1(&BayerFramePreProcessor::ExtractRedGreen, this);
        std::thread t2(&BayerFramePreProcessor::ExtractGreenBlue, this);

        t1.join();
        t2.join();
    }

    void Convert12To16Bit()
    {
        int j = 0;
        int dataSize = _size * 1.5; //16bit / 12bit

        for (long long i=0; i < dataSize; i += 3)
        {
            uint16_t pixel1 = (_data[i] << 4) + ((_data[i + 1] & 0xF0) >> 4);
            pixel1 &= 0xFFF;

            uint16_t pixel2 = ((_data[i + 1] & 0x0F) << 8) + _data[i + 2];

            _outputData[j] = pixel1;
            _outputData[j + 1] = pixel2;

            j += 2;
        }
    }

    void Convert14To16Bit()
    {

    }

    unsigned short *GetDataRed()
    {
        return _dataRed;
    }

    unsigned short *GetDataGreen()
    {
        return _dataGreen;
    }

    unsigned short *GetDataBlue()
    {
        return _dataBlue;
    }

    void SetData(unsigned char &data, int width, int height, OC::DataProvider::SourceFormat sourceFormat)
    {
        _data = &data;

        _width = width;
        _height = height;

        _size = _width * _height;

        _outputData = new unsigned short[_size];

        _dataRed = new unsigned short[_size];
        _dataGreen = new unsigned short[_size];
        _dataBlue = new unsigned short[_size];
    }
};

#endif // IFRAMEPROCESSOR_H

