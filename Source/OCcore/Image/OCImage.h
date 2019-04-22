// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef OCIMAGE_H
#define OCIMAGE_H

#include <cstring>
#include <fstream>

#include "ImageDefines.h"

namespace OC
{
    namespace Image
    {
        // TODO: Move to some general definition file
        enum class BayerPattern
        {
            RGGB,
            BGGR,
            GRBG,
            GBRG
        };

        class OCImage
        {
            unsigned int _width;
            unsigned int _height;
            // unsigned char* _data;

            BayerPattern _pattern;

            ImageType _type;

            void* _redData;
            void* _greenData;
            void* _blueData;

            // unsigned int _dataSize;
            unsigned int _dataLength;
            ImageFormat _format;

        public:
            OCImage();

            ~OCImage();

            void SetWidth(unsigned int width);

            void SetHeight(unsigned int height);

            void* RedChannel();

            void* GreenChannel();

            void* BlueChannel();

            void SetFormat(ImageFormat format);

            unsigned int Width() const;

            unsigned int Height() const;

            ImageFormat Format() const;

            ImageType Type() const;

            void SetType(ImageType type);

            // TODO: Should be called before Set*Channel() at the moment, later (see TODO below) it shouldn't be a problem anymore
            unsigned int DataLength() const;

            // TODO: Remove memcpy() when static allocator is implemented, just store pointer to data instead
            void SetRedChannel(void* redData);

            void SetGreenChannel(void* greenData);

            void SetBlueChannel(void* blueData);

            void SetBayerPattern(BayerPattern pattern);

            BayerPattern GetBayerPattern() const;
        };
    }
}

#endif // OCIMAGE_H
