#include "SHOODAKDebayer.h"

using namespace OC::DataProvider;

SHOODAKDebayer::SHOODAKDebayer(OCImage& image)
{
	redChannel = static_cast<unsigned short*>(image.RedChannel());
	greenChannel = static_cast<unsigned short*>(image.GreenChannel());
	blueChannel = static_cast<unsigned short*>(image.BlueChannel());

	_width = image.Width();
	_height = image.Height();

	SetColorOffsets(image.GetBayerPattern());
}

void SHOODAKDebayer::Process()
{
	BilinearFilterRed();
	BilinearFilterGreen();
	BilinearFilterBlue();
}

unsigned short* SHOODAKDebayer::GetDataRed()
{
	return nullptr;
}

unsigned short* SHOODAKDebayer::GetDataGreen()
{
	return nullptr;
}

unsigned short* SHOODAKDebayer::GetDataBlue()
{
	return nullptr;
}

void SHOODAKDebayer::BilinearFilterGreen() const
{
	for (auto rowIndex = colorOffsets[2]; rowIndex < _height; rowIndex += 2)
	{
		for (auto columnIndex = colorOffsets[3]; columnIndex < _width - 2; columnIndex += 2)
		{
			greenChannel[rowIndex * _width + columnIndex] = ((greenChannel[rowIndex * _width + columnIndex - 1] + greenChannel[rowIndex * _width + columnIndex + 1]) + (greenChannel[(rowIndex - 1) * _width + columnIndex] + greenChannel[(rowIndex + 1) * _width + columnIndex])) / 4;
		}
	}

	for (auto rowIndex = colorOffsets[4]; rowIndex < _height; rowIndex += 2)
	{
		for (auto columnIndex = colorOffsets[5]; columnIndex < _width - 2; columnIndex += 2)
		{
			greenChannel[rowIndex * _width + columnIndex] = ((greenChannel[rowIndex * _width + columnIndex - 1] + greenChannel[rowIndex * _width + columnIndex + 1]) + (greenChannel[(rowIndex - 1) * _width + columnIndex] + greenChannel[(rowIndex + 1) * _width + columnIndex])) / 4;
		}
	}
}

void SHOODAKDebayer::BilinearFilterRed() const
{
	for (auto rowIndex = colorOffsets[0]; rowIndex < _height; rowIndex += 2)
	{
		for (auto columnIndex = colorOffsets[1]; columnIndex < _width - 2; columnIndex += 2)
		{
			redChannel[rowIndex * _width + columnIndex] = ((redChannel[(rowIndex - 1) * _width + columnIndex - 1] + redChannel[(rowIndex - 1) * _width + columnIndex + 1]) +
				(redChannel[(rowIndex + 1) * _width + columnIndex - 1] + redChannel[(rowIndex + 1) * _width + columnIndex + 1])) / 4;

			redChannel[(rowIndex + 1) * _width + columnIndex] = (redChannel[(rowIndex + 1) * _width + columnIndex - 1] + redChannel[(rowIndex + 1) * _width + columnIndex + 1]) / 2;
			redChannel[rowIndex * _width + columnIndex + 1] = (redChannel[(rowIndex + 1) * _width + columnIndex + 1] + redChannel[(rowIndex - 1) * _width + columnIndex + 1]) / 2;
		}
	}
}

void SHOODAKDebayer::BilinearFilterBlue() const
{
	for (auto rowIndex = colorOffsets[6]; rowIndex < _height; rowIndex += 2)
	{
		for (auto columnIndex = colorOffsets[7]; columnIndex < _width - 2; columnIndex += 2)
		{
			blueChannel[rowIndex * _width + columnIndex] = ((blueChannel[(rowIndex - 1) * _width + columnIndex - 1] + blueChannel[(rowIndex - 1) * _width + columnIndex + 1]) +
				(blueChannel[(rowIndex + 1) * _width + columnIndex - 1] + blueChannel[(rowIndex + 1) * _width + columnIndex + 1])) / 4;

			blueChannel[(rowIndex + 1) * _width + columnIndex] = (blueChannel[(rowIndex + 1) * _width + columnIndex - 1] + blueChannel[(rowIndex + 1) * _width + columnIndex + 1]) / 2;
			blueChannel[rowIndex * _width + columnIndex + 1] = (blueChannel[(rowIndex + 1) * _width + columnIndex + 1] + blueChannel[(rowIndex - 1) * _width + columnIndex + 1]) / 2;
		}
	}
}

//TODO: Finish pattern layout, see also BilinearDebayer class
void SHOODAKDebayer::SetColorOffsets(BayerPattern pattern)
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
