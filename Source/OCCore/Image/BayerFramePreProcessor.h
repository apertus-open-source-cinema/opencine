#ifndef BAYERPROCESSOR_H
#define BAYERPROCESSOR_H

#include "IFrameProcessor.h"
#include "OCImage.h"

using namespace OC::DataProvider;

class BayerFramePreProcessor : public OC::DataProvider::IFrameProcessor
{
	unsigned char* _data;
	unsigned short* _outputData;
	unsigned int _size;

	OC::DataProvider::BayerPattern _pattern = BayerPattern::RGGB;

	unsigned short* dataUL; //upper-left data
	unsigned short* dataUR; //upper-right data
	unsigned short* dataLL; //lower-left data
	unsigned short* dataLR; //lower-right data

	unsigned short* _dataRed;
	unsigned short* _dataGreen;
	unsigned short* _dataBlue;

	unsigned int _width;
	unsigned int _height;

	void MapPatternToData();

	void ExtractOddRows() const;

	void ExtractEvenRows() const;

public:
	BayerFramePreProcessor();

	~BayerFramePreProcessor();

	virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, OC::DataProvider::SourceFormat sourceFormat) override;

	virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, OC::DataProvider::SourceFormat sourceFormat, BayerPattern pattern);

	void Process() override;

	void Convert12To16Bit() const;

	/*void Convert14To16Bit()
	{
	}*/

	unsigned short* GetDataRed() override;

	unsigned short* GetDataGreen() override;

	unsigned short* GetDataBlue() override;

	unsigned short* _linearizationTable = nullptr;
	unsigned int _linearizationLength = 0;

	void SetLinearizationData(unsigned short* linearizationTable, unsigned int linearizationLength);

	void SetData(unsigned char &data, int width, int height, OC::DataProvider::SourceFormat sourceFormat);
};

#endif // IFRAMEPROCESSOR_H

