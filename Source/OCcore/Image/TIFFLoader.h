// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef TIFFLOADER_H
#define TIFFLOADER_H

#include <functional>
#include <unordered_map>

#include "IImageLoader.h"
#include "OCImage.h"

#include "OCcore_export.h"

#include "Memory/StaticAllocator.h"

namespace OC
{
    namespace DataProvider
    {
        // Source: http://esr.ibiblio.org/?p=5095
        static inline uint8_t IsBigEndianMachine()
        {
            const uint16_t endianness = 256;
            return *reinterpret_cast<const uint8_t*>(&endianness);
        }

        struct TIFFHeader
        {
            uint16_t Identifier;
            uint16_t Version;
            uint32_t IFDOffset;
        };

        struct TIFFTag
        {
            uint16_t ID;
            uint16_t DataType;
            uint32_t DataCount;
            uint32_t DataOffset;
        };

        class OCCORE_EXPORT TIFFLoader : public IImageLoader
        {
            bool _swapEndianess;
            TIFFTag* tags;

            unsigned int _imageDataOffset;

            OC::Image::ImageFormat _bitsPerPixel;

            TIFFHeader ProcessHeader(char* buffer) const;

            void FindMainImage(unsigned char* data, unsigned int& ifdOffset, uint16_t& ifdCount);

            void SwapEndian(uint16_t& val) const;

            void SwapEndian(uint32_t& val) const;

            inline void SwapTagEndianess(TIFFTag& tag) const
            {
                SwapEndian(tag.ID);
                SwapEndian(tag.DataType);
                SwapEndian(tag.DataCount);

                if(tag.DataType == 3)
                {
                    tag.DataOffset = tag.DataOffset >> 16;
                    SwapEndian(reinterpret_cast<uint16_t&>(tag.DataOffset));
                }
                else if(tag.DataType == 4)
                {
                    SwapEndian(tag.DataOffset);
                }
            }

            void ProcessTags(std::unordered_map<int, std::function<void(TIFFTag&)>>& varMap, OC::Image::ImageFormat& bitsPerPixel,
                             unsigned int size, OC::Image::OCImage& image, unsigned char* data);

            void PreProcess(unsigned char* data, OC::Image::OCImage& image) const;

            void Cleanup() const;

        public:
            TIFFLoader();

            void ProcessIFDBlock() const;
            void Load(unsigned char* data, unsigned size, OC::Image::OCImage& image, IAllocator& allocator) override;
        };
    }
}

#endif // TIFFLOADER_H
