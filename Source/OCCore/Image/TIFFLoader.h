#ifndef TIFFLOADER_H
#define TIFFLOADER_H

#include <cstring>
#include <fstream>
#include <functional>
#include <iostream> //TODO: Remove when tests are finished
#include <unordered_map>

#include "Log/ILogger.h"
#include "OCImage.h"

#include "OCCore_export.h"

namespace OC
{
    namespace DataProvider
    {
        // Source: http://esr.ibiblio.org/?p=5095
        static inline uint8_t IsBigEndianMachine()
        {
            const uint16_t endianness = 256;
            return *(const uint8_t *)&endianness;
        }

        class IImageLoader
        {

        };

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

        class EXPORT_API TIFFLoader : public IImageLoader, Logger
        {
            bool _swapEndianess;
            uint16_t _ifdEntries;
            TIFFTag* tags;

            TIFFHeader ProcessHeader(char* buffer);

            inline void SwapEndian(uint16_t& val)
            {
                val = (val << 8) |         // left-shift always fills with zeros
                        ((uint16_t)val >> 8); // right-shift sign-extends, so force to zero
            }

            inline void SwapEndian(uint32_t& val)
            {
                val = (val<<24) | ((val<<8) & 0x00ff0000) |
                        ((val>>8) & 0x0000ff00) | (val>>24);
            }

            inline void SwapTagEndianess(TIFFTag& tag)
            {
                SwapEndian(tag.ID);
                SwapEndian(tag.DataType);
                SwapEndian(tag.DataCount);

                if(tag.DataType == 3)
                {
                    SwapEndian(reinterpret_cast<uint16_t&>(tag.DataOffset));
                }
                else if(tag.DataType == 4)
                {
                    SwapEndian(static_cast<uint32_t&>(tag.DataOffset));
                }
            }

            void ProcessTags(std::unordered_map<int, std::function<void(TIFFTag&)>>& varMap, ImageFormat& bitsPerPixel, unsigned int size, OC::DataProvider::OCImage& image, unsigned char* data);

            void PreProcess(unsigned char* data, OC::DataProvider::OCImage& image);

            void Cleanup();

        public:
            TIFFLoader(unsigned char* data, unsigned int size, OCImage& image);
        };
    }
}

#endif //TIFFLOADER_H

