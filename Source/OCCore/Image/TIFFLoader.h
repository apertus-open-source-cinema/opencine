#ifndef TIFFLOADER_H
#define TIFFLOADER_H

#include <fstream>
#include <iostream> //TODO: Remove when tests are finished
#include <unordered_map>

#include "OCImage.h"

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

        class TIFFLoader : public IImageLoader
        {
            bool _swapEndianess;
            uint16_t _ifdEntries;

        public:
            TIFFLoader(unsigned char* data, unsigned int size, OC::DataProvider::OCImage& image) :
                _swapEndianess(false)
            {
                if((data[0] << 8 | data[1]) == 0x4d4d && !IsBigEndianMachine())
                {
                    _swapEndianess = true;
                }

                TIFFHeader header = ProcessHeader((char*)data);

                memcpy(&_ifdEntries, data + header.IFDOffset, sizeof(_ifdEntries));
                if(_swapEndianess)
                {
                    SwapEndian(_ifdEntries);
                }

                TIFFTag* tags = new TIFFTag[_ifdEntries];
                memcpy(tags, data + header.IFDOffset + sizeof(_ifdEntries), sizeof(TIFFTag) * _ifdEntries);

                ImageFormat bitsPerPixel = ImageFormat::Integer12;
                std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
                varMap.insert(std::make_pair(256, [&image] (TIFFTag& tag) { image.SetWidth(tag.DataOffset); }));
                varMap.insert(std::make_pair(257, [&image] (TIFFTag& tag) { image.SetHeight(tag.DataOffset); }));
                varMap.insert(std::make_pair(258, [&bitsPerPixel] (TIFFTag& tag)
                {
                                  bitsPerPixel = static_cast<ImageFormat>(tag.DataOffset);
                              }));
                varMap.insert(std::make_pair(273, [&/*&data, &buffer, &width, &height, &bitsPerPixel*/] (TIFFTag& tag) mutable
                {
                                  unsigned int size = (unsigned int)(image.Width() * image.Height() * ((float)bitsPerPixel / 8.0f));
                                  image.SetData((unsigned char*)data + tag.DataOffset, size);
                              }));

                for(int i = 0; i < _ifdEntries; i++)
                {
                    if(_swapEndianess)
                    {
                        SwapTagEndianess(tags[i]);
                    }

                    std::cout << "Tag ID: " << tags[i].ID << std::endl;

                    auto it = varMap.find(tags[i].ID);
                    if(it != varMap.end())
                    {
                        (*it).second(tags[i]);
                    }
                }
            }

            TIFFHeader ProcessHeader(char* buffer)
            {
                TIFFHeader header;
                memcpy(&header, buffer, sizeof(TIFFHeader));

                if(_swapEndianess)
                {
                    SwapEndian(header.Version);
                    SwapEndian(header.IFDOffset);
                }

                return header;
            }

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
        };
    }
}

#endif //TIFFLOADER_H

