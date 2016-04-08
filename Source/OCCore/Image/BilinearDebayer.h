#ifndef BILINEARDEBAYER_H
#define BILINEARDEBAYER_H

#include "IFrameProcessor.h"
#include "OCImage.h"

namespace OC
{
	namespace DataProvider
	{
		class BilinearDebayer : public IFrameProcessor
		{
			unsigned short* redChannel;
			unsigned short* greenChannel;
			unsigned short* blueChannel;

			unsigned int _width;
			unsigned int _height;

		public:
			BilinearDebayer(OCImage& image)
			{
				redChannel = (unsigned short*)image.RedChannel();
				greenChannel = (unsigned short*)image.GreenChannel();
				blueChannel = (unsigned short*)image.BlueChannel();

				_width = image.Width();
				_height = image.Height();
			}

			void BilinearFilterGreen()
			{
				unsigned int rowIndex = 0;
				unsigned int columnIndex = 0;

				for (rowIndex = 1; rowIndex < _height; rowIndex += 2)
				{
					for (columnIndex = 2; columnIndex < _width - 2; columnIndex += 2)
					{
						greenChannel[rowIndex * _width + columnIndex] = ((greenChannel[rowIndex * _width + columnIndex - 1] + greenChannel[rowIndex * _width + columnIndex + 1]) + (greenChannel[(rowIndex - 1) * _width + columnIndex] + greenChannel[(rowIndex + 1) * _width + columnIndex])) / 4;
					}
				}

				for (rowIndex = 2; rowIndex < _height; rowIndex += 2)
				{
					for (columnIndex = 1; columnIndex < _width - 2; columnIndex += 2)
					{
						greenChannel[rowIndex * _width + columnIndex] = ((greenChannel[rowIndex * _width + columnIndex - 1] + greenChannel[rowIndex * _width + columnIndex + 1]) + (greenChannel[(rowIndex - 1) * _width + columnIndex] + greenChannel[(rowIndex + 1) * _width + columnIndex])) / 4;
					}
				}
			}

			void BilinearFilterRed()
			{
				unsigned int rowIndex = 0;
				unsigned int columnIndex = 0;

				for (rowIndex = 1; rowIndex < _height; rowIndex += 2)
				{
					for (columnIndex = 2; columnIndex < _width - 2; columnIndex += 2)
					{
						redChannel[rowIndex * _width + columnIndex] = ((redChannel[(rowIndex - 1) * _width + columnIndex - 1] + redChannel[(rowIndex - 1) * _width + columnIndex + 1]) +
							(redChannel[(rowIndex + 1) * _width + columnIndex - 1] + redChannel[(rowIndex + 1) * _width + columnIndex + 1])) / 4;

						redChannel[(rowIndex + 1) * _width + columnIndex] = (redChannel[(rowIndex + 1) * _width + columnIndex - 1] + redChannel[(rowIndex + 1) * _width + columnIndex + 1]) / 2;
						redChannel[rowIndex * _width + columnIndex + 1] = (redChannel[(rowIndex + 1) * _width + columnIndex + 1] + redChannel[(rowIndex - 1) * _width + columnIndex + 1]) / 2;
					}
				}
			}

			void BilinearFilterBlue()
			{
				unsigned int rowIndex = 0;
				unsigned int columnIndex = 0;

				for (rowIndex = 2; rowIndex < _height; rowIndex += 2)
				{
					for (columnIndex = 1; columnIndex < _width - 2; columnIndex += 2)
					{
						blueChannel[rowIndex * _width + columnIndex] = ((blueChannel[(rowIndex - 1) * _width + columnIndex - 1] + blueChannel[(rowIndex - 1) * _width + columnIndex + 1]) +
							(blueChannel[(rowIndex + 1) * _width + columnIndex - 1] + blueChannel[(rowIndex + 1) * _width + columnIndex + 1])) / 4;

						blueChannel[(rowIndex + 1) * _width + columnIndex] = (blueChannel[(rowIndex + 1) * _width + columnIndex - 1] + blueChannel[(rowIndex + 1) * _width + columnIndex + 1]) / 2;
						blueChannel[rowIndex * _width + columnIndex + 1] = (blueChannel[(rowIndex + 1) * _width + columnIndex + 1] + blueChannel[(rowIndex - 1) * _width + columnIndex + 1]) / 2;
					}
				}
			}

			virtual void Process()
			{
				BilinearFilterRed();
				BilinearFilterGreen();
				BilinearFilterBlue();
			}

			virtual void SetData(unsigned char& data, unsigned int width, unsigned int height, SourceFormat sourceFormat) {}

			virtual unsigned short* GetDataRed()
			{
				return nullptr;
			}

			virtual unsigned short* GetDataGreen()
			{
				return nullptr;
			}

			virtual unsigned short* GetDataBlue()
			{
				return nullptr;
			}
		};
	}
}
#endif //BILINEARDEBAYER_H
