#include "BayerFramePreProcessor.h"

#include <Log/Logger.h>

void BayerFramePreProcessor::MapPatternToData()
{
	switch (_pattern)
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

void BayerFramePreProcessor::ExtractOddRows() const
{
#pragma omp parallel for
	for (int rowIndex = 0; rowIndex < _height; rowIndex += 2)
	{
		for (int columnIndex = 0; columnIndex < _width; columnIndex++)
		{
			if (columnIndex % 2)
			{
				dataUR[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
			}
			else
			{
				dataUL[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
			}
		}
	}
}

void BayerFramePreProcessor::ExtractEvenRows() const
{
#pragma omp parallel for
	for (int rowIndex = 1; rowIndex < _height; rowIndex += 2)
	{
		for (int columnIndex = 0; columnIndex < _width; columnIndex++)
		{
			if (columnIndex % 2)
			{
				dataLR[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
			}
			else
			{
				dataLL[rowIndex * _width + columnIndex] = _outputData[rowIndex * _width + columnIndex];
			}
		}
	}
}

BayerFramePreProcessor::BayerFramePreProcessor() :
	_data(nullptr),
	_outputData(nullptr),
	_size(0),
	dataUL(nullptr),
	dataUR(nullptr),
	dataLL(nullptr),
	dataLR(nullptr),
	_dataRed(nullptr),
	_dataGreen(nullptr),
	_dataBlue(nullptr),
	_width(0),
	_height(0)
{
}

BayerFramePreProcessor::~BayerFramePreProcessor()
{
	//	delete [] _dataRed;
	//	delete [] _dataGreen;
	//	delete [] _dataBlue;
	//
	//	delete [] _outputData;
}

//void BayerFramePreProcessor::SetData(unsigned char& data, unsigned int width, unsigned int height, SourceFormat sourceFormat)
//{
//	_data = &data;
//
//	_width = width;
//	_height = height;
//
//	_size = _width * _height;
//
//	_outputData = new unsigned short[_size];
//
//	//_dataRed = new unsigned short[_size * 2];
//	//_dataGreen = new unsigned short[_size * 2];
//	//_dataBlue = new unsigned short[_size * 2];
//
//	MapPatternToData();
//}

// TODO: Uncomment when it's required again
//void BayerFramePreProcessor::SetData(unsigned char& data, unsigned int width, unsigned int height, SourceFormat sourceFormat, BayerPattern pattern)
//{
//	_data = &data;
//
//	_width = width;
//	_height = height;
//
//	_size = _width * _height;
//
//	_outputData = new unsigned short[_size];
//
//    //_dataRed = new unsigned short[_size];
//    //_dataGreen = new unsigned short[_size];
//    //_dataBlue = new unsigned short[_size];
//
//	_pattern = pattern;
//
//	MapPatternToData();
//}

void BayerFramePreProcessor::SetData(unsigned char& data, OCImage& image)
{
	_data = &data;

	_width = image.Width();
	_height = image.Height();

	_size = _width * _height;

	_outputData = new unsigned short[_size];

	_dataRed = static_cast<unsigned short*>(image.RedChannel());
	_dataGreen = static_cast<unsigned short*>(image.GreenChannel());
	_dataBlue = static_cast<unsigned short*>(image.BlueChannel());

	_pattern = image.GetBayerPattern();

	MapPatternToData();
}

void BayerFramePreProcessor::Process()
{
	OC_LOG_INFO("12->16bit conversion");
	Convert12To16Bit();

	OC_LOG_INFO("Extract rows");
	std::thread t1(&BayerFramePreProcessor::ExtractOddRows, this);
	std::thread t2(&BayerFramePreProcessor::ExtractEvenRows, this);

	t1.join();
	t2.join();

	//OC_LOG_INFO("Extract finished");
}

void BayerFramePreProcessor::Convert12To16Bit() const
{
	int j = 0;
	int dataSize = static_cast<int>(_size * 1.5f); //16bit / 12bit

	//Take every 3 bytes to extract 2 x 12bits
	for (long long i = 0; i < dataSize; i += 3)
	{
		uint16_t pixel1 = (_data[i] << 4) + ((_data[i + 1] & 0xF0) >> 4);
		pixel1 &= 0xFFF;

		uint16_t pixel2 = ((_data[i + 1] & 0x0F) << 8) + _data[i + 2];

		//		if (_linearizationTable != nullptr)
		//		{
		//			_outputData[j] = _linearizationTable[pixel1];
		//			_outputData[j + 1] = _linearizationTable[pixel2];
		//		}
		//		else
		//		{
		_outputData[j] = pixel1;
		_outputData[j + 1] = pixel2;
		//		}

				/*if (_outputData[j] > 256)
				{
					_outputData[j] -= 256;
				}
				else
				{
					_outputData[j] = 0;
				}

				if (_outputData[j + 1] > 256)
				{
					_outputData[j + 1] -= 256;
				}
				else
				{
					_outputData[j + 1] = 0;
				}*/

		j += 2;
	}
}

unsigned short*BayerFramePreProcessor::GetDataRed()
{
	return _dataRed;
}

unsigned short*BayerFramePreProcessor::GetDataGreen()
{
	return _dataGreen;
}

unsigned short*BayerFramePreProcessor::GetDataBlue()
{
	return _dataBlue;
}

void BayerFramePreProcessor::SetLinearizationData(unsigned short* linearizationTable, unsigned int linearizationLength)
{
	_linearizationTable = linearizationTable;
	_linearizationLength = linearizationLength;
}

// TODO: Uncomment when it's required again
//void BayerFramePreProcessor::SetData(unsigned char& data, int width, int height, SourceFormat sourceFormat)
//{
//	_data = &data;
//
//	_width = width;
//	_height = height;
//
//	_size = _width * _height;
//
//	_outputData = new unsigned short[_size];
//
//    //_dataRed = new unsigned short[_size];
//    //_dataGreen = new unsigned short[_size];
//    //_dataBlue = new unsigned short[_size];
//}