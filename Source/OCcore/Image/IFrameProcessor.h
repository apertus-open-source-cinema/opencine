// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IFRAMEPROCESSOR_H
#define IFRAMEPROCESSOR_H

#include <inttypes.h>

#include "ImageDefines.h"

namespace OC
{
    namespace Image
    {
        class OCImage;
    }

    namespace DataProvider
    {
        class IFrameProcessor
        {
        public:
            virtual ~IFrameProcessor();

            virtual void Process() = 0;
            virtual void SetData(uint8_t* /*data*/, OC::Image::OCImage& /*image*/, OC::Image::ImageFormat /*imageFormat*/);
            virtual void SetData(uint16_t* /*imageData*/, OC::Image::OCImage& /*image*/);

            virtual unsigned short* GetDataRed() = 0;
            virtual unsigned short* GetDataGreen() = 0;
            virtual unsigned short* GetDataBlue() = 0;
        };
    }
}
#endif // IFRAMEPROCESSOR_H
