// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef OCIMAGE_H
#define OCIMAGE_H

#include <cstring>
#include <fstream>

#include "ImageDefines.h"

namespace OC
{
	namespace DataProvider
	{
		//TODO: Move to some general definition file
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
			//unsigned char* _data;

			BayerPattern _pattern;

			ImageType _type;

			void* _redData;
			void* _greenData;
			void* _blueData;

			//unsigned int _dataSize;
			unsigned int _dataLength;
			ImageFormat _format;

		public:
			OCImage() :
				_width(0),
				_height(0),
				_pattern(BayerPattern::RGGB),
				_redData(nullptr),
				_greenData(nullptr),
				_blueData(nullptr),
				_dataLength(0)
			{
			}

			~OCImage()
			{
				delete[](short*)_redData;
				delete[](short*)_greenData;
				delete[](short*)_blueData;
			}

			void SetWidth(unsigned int width)
			{
				_width = width;
			}

			void SetHeight(unsigned int height)
			{
				_height = height;
			}

			void* RedChannel()
			{
				return _redData;
			}

			void* GreenChannel()
			{
				return _greenData;
			}

			void* BlueChannel()
			{
				return _blueData;
			}

			void SetFormat(ImageFormat format)
			{
				_format = format;
			}

			unsigned int Width() const
			{
				return _width;
			}

			unsigned int Height() const
			{
				return _height;
			}

			ImageFormat Format() const
			{
				return _format;
			}

			ImageType Type() const
			{
				return _type;
			}

			void SetType(ImageType type)
			{
				_type = type;
			}

			//TODO: Should be called before Set*Channel() at the moment, later (see TODO below) it shouldn't be a problem anymore
			unsigned int DataLength() const
			{
				return _dataLength;
			}

			//TODO: Remove memcpy() when static allocator is implemented, just store pointer to data instead
			void SetRedChannel(void* redData)
			{
				_dataLength = _width * _height * sizeof(unsigned short);

				if (_redData == nullptr)
				{
					_redData = new unsigned short[_dataLength];
				}

				memmove(_redData, redData, _dataLength);
			}

			void SetGreenChannel(void* greenData)
			{
				if (_greenData == nullptr)
				{
					_greenData = new unsigned short[_dataLength];
				}

				memmove(_greenData, greenData, _dataLength);
			}

			void SetBlueChannel(void* blueData)
			{
				if (_blueData == nullptr)
				{
					_blueData = new unsigned short[_dataLength];
				}

				memmove(_blueData, blueData, _dataLength);
			}

			void SetBayerPattern(BayerPattern pattern)
			{
				_pattern = pattern;
			}

			BayerPattern GetBayerPattern() const
			{
				return _pattern;
			}
		};
	}
}

#endif //OCIMAGE_H
