#ifndef IFRAMEPROCESSOR_H
#define IFRAMEPROCESSOR_H

#include <inttypes.h>

#include "ImageDefines.h"

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
            virtual void SetData(uint8_t* /*data*/, OCImage& /*image*/, ImageFormat /*imageFormat*/) {}
            //virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, SourceFormat sourceFormat) = 0;
            virtual unsigned short* GetDataRed() = 0;
            virtual unsigned short* GetDataGreen() = 0;
            virtual unsigned short* GetDataBlue() = 0;
        };
    }
}
#endif //IFRAMEPROCESSOR_H
