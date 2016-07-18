#ifndef BILINEARDEBAYER_H
#define BILINEARDEBAYER_H

#include "IFrameProcessor.h"
#include "OCImage.h"

#include <thread>

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

			unsigned int colorOffsets[8] = { 1, 1, 1, 1, 1, 1, 1, 1 }; //R G1 G2 B, first: row, second: column

		public:
			explicit BilinearDebayer(OCImage& image)
			{
				redChannel = static_cast<unsigned short*>(image.RedChannel());
				greenChannel = static_cast<unsigned short*>(image.GreenChannel());
				blueChannel = static_cast<unsigned short*>(image.BlueChannel());

				_width = image.Width();
				_height = image.Height();

				SetColorOffsets(image.GetBayerPattern());
			}

			void BilinearFilterGreen() const
			{
				for (auto rowIndex = colorOffsets[2]; rowIndex < _height; rowIndex += 2)
				{
					for (auto columnIndex = colorOffsets[3]; columnIndex < _width - 2; columnIndex += 2)
					{
						greenChannel[rowIndex * _width + columnIndex] = ((greenChannel[rowIndex * _width + columnIndex - 1] + greenChannel[rowIndex * _width + columnIndex + 1]) + (greenChannel[(rowIndex - 1) * _width + columnIndex] + greenChannel[(rowIndex + 1) * _width + columnIndex])) * 0.25f;
					}
				}

				for (auto rowIndex = colorOffsets[4]; rowIndex < _height; rowIndex += 2)
				{
					for (auto columnIndex = colorOffsets[5]; columnIndex < _width - 2; columnIndex += 2)
					{
						greenChannel[rowIndex * _width + columnIndex] = ((greenChannel[rowIndex * _width + columnIndex - 1] + greenChannel[rowIndex * _width + columnIndex + 1]) + (greenChannel[(rowIndex - 1) * _width + columnIndex] + greenChannel[(rowIndex + 1) * _width + columnIndex])) * 0.25f;
					}
				}
			}

			void BilinearFilterRed() const
			{
				for (auto rowIndex = colorOffsets[0]; rowIndex < _height; rowIndex += 2)
				{
					for (auto columnIndex = colorOffsets[1]; columnIndex < _width - 2; columnIndex += 2)
					{
						redChannel[rowIndex * _width + columnIndex] = ((redChannel[(rowIndex - 1) * _width + columnIndex - 1] + redChannel[(rowIndex - 1) * _width + columnIndex + 1]) +
							(redChannel[(rowIndex + 1) * _width + columnIndex - 1] + redChannel[(rowIndex + 1) * _width + columnIndex + 1])) * 0.25f;

						redChannel[(rowIndex + 1) * _width + columnIndex] = (redChannel[(rowIndex + 1) * _width + columnIndex - 1] + redChannel[(rowIndex + 1) * _width + columnIndex + 1]) * 0.5f;
						redChannel[rowIndex * _width + columnIndex + 1] = (redChannel[(rowIndex + 1) * _width + columnIndex + 1] + redChannel[(rowIndex - 1) * _width + columnIndex + 1]) * 0.5f;
					}
				}
			}

			void BilinearFilterBlue() const
			{
				for (auto rowIndex = colorOffsets[6]; rowIndex < _height; rowIndex += 2)
				{
					for (auto columnIndex = colorOffsets[7]; columnIndex < _width - 2; columnIndex += 2)
					{
						blueChannel[rowIndex * _width + columnIndex] = ((blueChannel[(rowIndex - 1) * _width + columnIndex - 1] + blueChannel[(rowIndex - 1) * _width + columnIndex + 1]) +
							(blueChannel[(rowIndex + 1) * _width + columnIndex - 1] + blueChannel[(rowIndex + 1) * _width + columnIndex + 1])) * 0.25f;

						blueChannel[(rowIndex + 1) * _width + columnIndex] = (blueChannel[(rowIndex + 1) * _width + columnIndex - 1] + blueChannel[(rowIndex + 1) * _width + columnIndex + 1]) * 0.5f;
						blueChannel[rowIndex * _width + columnIndex + 1] = (blueChannel[(rowIndex + 1) * _width + columnIndex + 1] + blueChannel[(rowIndex - 1) * _width + columnIndex + 1]) * 0.5f;
					}
				}
			}

			//TODO: Finish pattern layout
			void SetColorOffsets(BayerPattern pattern)
			{
				switch (pattern)
				{
				case BayerPattern::RGGB:
					break;
				case BayerPattern::BGGR:
					break;
				case BayerPattern::GRBG:
					colorOffsets[0] = 1;
					colorOffsets[1] = 2;
					colorOffsets[2] = 1;
					colorOffsets[3] = 2;
					colorOffsets[4] = 2;
					colorOffsets[5] = 1;
					colorOffsets[6] = 2;
					colorOffsets[7] = 1;
					break;
				case BayerPattern::GBRG:
					colorOffsets[0] = 2;
					colorOffsets[1] = 1;
					colorOffsets[2] = 1;
					colorOffsets[3] = 2;
					colorOffsets[4] = 2;
					colorOffsets[5] = 1;
					colorOffsets[6] = 1;
					colorOffsets[7] = 2;
					break;
				}
			}

			void Process() override
			{
                std::thread redThread(&BilinearDebayer::BilinearFilterRed, this);
                std::thread greenThread(&BilinearDebayer::BilinearFilterGreen, this);
                std::thread blueThread(&BilinearDebayer::BilinearFilterBlue, this);

                redThread.join();
                greenThread.join();
                blueThread.join();
			}

			unsigned short* GetDataRed() override
			{
				return nullptr;
			}

			unsigned short* GetDataGreen() override
			{
				return nullptr;
			}

			unsigned short* GetDataBlue() override
			{
				return nullptr;
			}
		};
	}
}
#endif //BILINEARDEBAYER_H
