#ifndef TIFFLOADER_H
#define TIFFLOADER_H

#include <functional>
#include <unordered_map>

#include "OCImage.h"
#include "IImageLoader.h"

#include "OCCore_export.h"

namespace OC
{
	namespace DataProvider
	{
		// Source: http://esr.ibiblio.org/?p=5095
		static inline uint8_t IsBigEndianMachine()
		{
			const uint16_t endianness = 256;
			return *reinterpret_cast<const uint8_t *>(&endianness);
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

			TIFFHeader ProcessHeader(char* buffer);

			inline void SwapEndian(uint16_t& val);

			inline void SwapEndian(uint32_t& val);

			inline void SwapTagEndianess(TIFFTag& tag)
			{
				SwapEndian(tag.ID);
				SwapEndian(tag.DataType);
				SwapEndian(tag.DataCount);

				if (tag.DataType == 3)
				{
					tag.DataOffset = tag.DataOffset >> 16;
					SwapEndian(reinterpret_cast<uint16_t&>(tag.DataOffset));
				}
				else if (tag.DataType == 4)
				{
					SwapEndian(tag.DataOffset);
				}
			}

			void ProcessTags(std::unordered_map<int, std::function<void(TIFFTag&)>>& varMap, ImageFormat& bitsPerPixel, unsigned int size, OC::DataProvider::OCImage& image, unsigned char* data);

			void PreProcess(unsigned char* data, OC::DataProvider::OCImage& image) const;

			void Cleanup() const;

		public:
			void ProcessIFDBlock();
			void LoadImage(unsigned char* data, unsigned size, OCImage& image);
			TIFFLoader(unsigned char* data, unsigned int size, OCImage& image);
		};
	}
}

#endif //TIFFLOADER_H
