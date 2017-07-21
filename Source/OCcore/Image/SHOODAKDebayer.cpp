// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "BilinearDebayer.h"
#include "SHOODAKDebayer.h"

#include <random>
#include <thread>

using namespace OC::DataProvider;

SHOODAKDebayer::SHOODAKDebayer(OCImage& image)
{
    BilinearDebayer* debayer = new BilinearDebayer(image);
    debayer->Process();

    redChannel = static_cast<unsigned short*>(image.RedChannel());
	greenChannel = static_cast<unsigned short*>(image.GreenChannel());
	blueChannel = static_cast<unsigned short*>(image.BlueChannel());

	_width = image.Width();
	_height = image.Height();

    //SetColorOffsets(image.GetBayerPattern());
}

void SHOODAKDebayer::Process()
{
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

//TODO: Finish pattern layout, see also BilinearDebayer class
//void SHOODAKDebayer::SetColorOffsets(BayerPattern pattern)
//{
//	switch (pattern)
//	{
//	case BayerPattern::RGGB:
//		break;
//	case BayerPattern::BGGR:
//		break;
//	case BayerPattern::GRBG:
//		colorOffsets[0] = 1;
//		colorOffsets[1] = 2;
//		colorOffsets[2] = 1;
//		colorOffsets[3] = 2;
//		colorOffsets[4] = 2;
//		colorOffsets[5] = 1;
//		colorOffsets[6] = 2;
//		colorOffsets[7] = 1;
//		break;
//	case BayerPattern::GBRG:
//		colorOffsets[0] = 2;
//		colorOffsets[1] = 1;
//		colorOffsets[2] = 1;
//		colorOffsets[3] = 2;
//		colorOffsets[4] = 2;
//		colorOffsets[5] = 1;
//		colorOffsets[6] = 1;
//		colorOffsets[7] = 2;
//		break;
//	}
//}

void SHOODAKDebayer::SelectRandomPixels()
{
	unsigned int randomPixelCount = _width * _height * 0.25; //25% percent for now, later it will be configurable
	unsigned int* randomPixelPos = new unsigned int[randomPixelCount];

    //std::random_device rd;
    std::mt19937 gen(123456);
	std::uniform_int_distribution<> dis(0, randomPixelCount);

	for (int index = 0; index < randomPixelCount; ++index)
	{
		randomPixelPos[index] = dis(gen);
	}
}
