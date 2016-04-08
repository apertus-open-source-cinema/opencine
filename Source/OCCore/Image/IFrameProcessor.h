#ifndef IFRAMEPROCESSOR_H
#define IFRAMEPROCESSOR_H

#include <thread>

#include "ImageDefines.h"

namespace OC
{
	namespace DataProvider
	{
		class IFrameProcessor
		{
		public:
			virtual ~IFrameProcessor() {}

			virtual void Process() = 0;
			virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, SourceFormat sourceFormat) = 0;
			virtual unsigned short* GetDataRed() = 0;
			virtual unsigned short* GetDataGreen() = 0;
			virtual unsigned short* GetDataBlue() = 0;
		};

		//IFrameProcessor::~IFrameProcessor() {}
	}
}
#endif //IFRAMEPROCESSOR_H
