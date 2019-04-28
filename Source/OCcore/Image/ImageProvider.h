// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "ImageDefines.h"

#include "OCcore_export.h"

class IAllocator;

namespace OC
{
    namespace Image
    {
        class OCImage;
    }

    namespace DataProvider
    {
        class IImageLoader;

        class OCCORE_EXPORT ImageProvider
        {
            // FIXME: Evaluate usage of FileFormat enum as key
            std::unordered_map<OC::Image::FileFormat, std::shared_ptr<IImageLoader>, OC::Image::FileFormatHash> _imageLoaders;

            IImageLoader* FindSuitableLoader(uint8_t* data, std::streamsize size) const;

        public:
            ImageProvider();

            bool ReadBinaryFile(std::string fileName, std::streamsize& length, unsigned char*& fileData) const;
            void Load(std::string fileName, OC::Image::FileFormat format, OC::Image::OCImage& image, IAllocator& allocator) const;
        };
    }
}

#endif // IMAGEPROVIDER_H
