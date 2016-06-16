#ifndef IFRAMEPROCESSOR_H
#define IFRAMEPROCESSOR_H

namespace OC
{
	namespace DataProvider
	{
		class OCImage;

		class IFrameProcessor
		{
		public:
			virtual ~IFrameProcessor() {}

			virtual void Process() = 0;
			virtual void SetData(unsigned char& data, OCImage& image) {}
			//virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, SourceFormat sourceFormat) = 0;
			virtual unsigned short* GetDataRed() = 0;
			virtual unsigned short* GetDataGreen() = 0;
			virtual unsigned short* GetDataBlue() = 0;
		};

		//IFrameProcessor::~IFrameProcessor() {}
	}
}
#endif //IFRAMEPROCESSOR_H
