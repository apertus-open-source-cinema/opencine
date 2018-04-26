// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "TIFFLoader.h"

#include <iostream>
#include <memory>

#include "Log/Logger.h"

#include "BayerFramePreProcessor.h"

using namespace OC::DataProvider;

unsigned char* imageData;
unsigned short* linearizationTable;
unsigned int linearizationLength;

IAllocator* _allocator = nullptr;

TIFFLoader::TIFFLoader() :
	_swapEndianess(false),
	_imageDataOffset(0)
{
}

void TIFFLoader::Cleanup() const
{
	if (imageData != nullptr)
	{
		delete [] imageData;
	}

	if (tags != nullptr)
	{
		delete [] tags;
	}
}

void TIFFLoader::ProcessIFDBlock() const
{
}

TIFFHeader TIFFLoader::ProcessHeader(char* buffer) const
{
	TIFFHeader header;
	memcpy(&header, buffer, sizeof(TIFFHeader));

	if (_swapEndianess)
	{
		SwapEndian(header.Version);
		SwapEndian(header.IFDOffset);
	}

	return header;
}

//Check first tag (TIFF are usually sorted ascending) of IFD for image SubFile type
//if value != 0 then search for SUbIFD tag (0x14a) and use the offset to next IFD, go there and repeat the procedure
//Caution: "NextIFD" entry is not used in DNG
void TIFFLoader::FindMainImage(unsigned char* data, unsigned int& ifdOffset, uint16_t& ifdCount)
{
	ifdCount = 0;

	auto imageFound = false;
	while (imageFound != true)
	{
		memcpy(&ifdCount, data + ifdOffset, sizeof(uint16_t));
		if (_swapEndianess)
		{
			SwapEndian(ifdCount);
		}

		tags = new TIFFTag[ifdCount];
		memcpy(tags, data + ifdOffset + sizeof(ifdCount), sizeof(TIFFTag) * ifdCount);

		if (_swapEndianess)
		{
			SwapTagEndianess(tags[0]);
		}

		if (tags[0].ID == 254 && tags[0].DataOffset == 0) //TODO: Replace tiff tag ID by enum
		{
			imageFound = true;
		}
		else
		{
			for (int tagIndex = 0; tagIndex < ifdCount; tagIndex++)
			{
				if (_swapEndianess)
				{
					SwapTagEndianess(tags[tagIndex]);
				}

				if (tags[tagIndex].ID == 0x14a)
				{
					ifdOffset = tags[tagIndex].DataOffset; //12 bytes per tag
					break;
				}
			}
		}
	}
}

void TIFFLoader::Load(unsigned char* data, unsigned size, OCImage& image, IAllocator& allocator)
{
	if ((data[0] << 8 | data[1]) == 0x4d4d && !IsBigEndianMachine())
	{
		_swapEndianess = true;
	}

	TIFFHeader header = ProcessHeader(reinterpret_cast<char*>(data));

	uint16_t ifdCount = 0;
	unsigned int ifdOffset = header.IFDOffset;

	FindMainImage(data, ifdOffset, ifdCount);
	
	std::unordered_map<int, std::string> tagNames = CreateTIFFTagMap();

	ImageFormat bitsPerPixel = ImageFormat::Integer12;
	std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
	ProcessTags(varMap, bitsPerPixel, size, image, data);

	for (int i = 0; i < ifdCount; i++)
	{
		if (_swapEndianess)
		{
			SwapTagEndianess(tags[i]);
		}

		std::cout << "Tag ID: " << tags[i].ID << std::endl;
        OC_LOG_INFO("Tag ID: " + std::to_string(tags[i].ID));

		auto it = varMap.find(tags[i].ID);
		if (it != varMap.end())
		{
			(*it).second(tags[i]);
		}
	}

    _allocator = &allocator;
    PreProcess(data, image);

	Cleanup();
}

inline void TIFFLoader::SwapEndian(uint16_t& val) const
{
    val = (val << 8) | // left-shift always fills with zeros
		(static_cast<uint16_t>(val) >> 8); // right-shift sign-extends, so force to zero
}

inline void TIFFLoader::SwapEndian(uint32_t& val) const
{
	val = (val << 24) | ((val << 8) & 0x00ff0000) |
		((val >> 8) & 0x0000ff00) | (val >> 24);
}

void TIFFLoader::ProcessTags(std::unordered_map<int, std::function<void(TIFFTag&)>>& varMap, ImageFormat& bitsPerPixel, unsigned int size, OCImage& image, unsigned char* data)
{
	//std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
	varMap.insert(std::make_pair(256, [&image](TIFFTag& tag) { image.SetWidth(tag.DataOffset); }));
	varMap.insert(std::make_pair(257, [&image](TIFFTag& tag) { image.SetHeight(tag.DataOffset); }));
	varMap.insert(std::make_pair(33422, [&image](TIFFTag& tag) //Bayer pattern
	{
		image.SetType(ImageType::Bayer);
		switch (tag.DataOffset)
		{
			//read right to left to get right values
			//e.g. RGGB -> 02 B | 01 G | 01 G | 00 R
		case 0x02010100:
			image.SetBayerPattern(BayerPattern::RGGB);
			break;
		case 0x00010102:
			image.SetBayerPattern(BayerPattern::BGGR);
			break;
		case 0x01000201:
			image.SetBayerPattern(BayerPattern::GBRG);
			break;
		case 0x01020001:
			image.SetBayerPattern(BayerPattern::GRBG);
			break;
		}
	}));

	varMap.insert(std::make_pair(50712, [=](TIFFTag& tag) //Bayer pattern
	{
		linearizationLength = tag.DataCount;
		linearizationTable = new unsigned short[linearizationLength];

		memcpy(linearizationTable, data + tag.DataOffset, sizeof(unsigned short) * linearizationLength);
	}));

	varMap.insert(std::make_pair(258, [&bitsPerPixel](TIFFTag& tag)
	{
		bitsPerPixel = static_cast<ImageFormat>(tag.DataOffset);
	}));

	varMap.insert(std::make_pair(273, [=, &image](TIFFTag& tag) mutable
	{
		_imageDataOffset = tag.DataOffset;
	}));
}

void TIFFLoader::PreProcess(unsigned char* data, OCImage& image) const
{
	auto start = std::chrono::high_resolution_clock::now();

    std::unique_ptr<BayerFramePreProcessor> frameProcessor(new BayerFramePreProcessor());

    unsigned int dataSize = image.Width() * image.Height();
    image.SetRedChannel(_allocator->Allocate(dataSize));
    image.SetGreenChannel(_allocator->Allocate(dataSize));
    image.SetBlueChannel(_allocator->Allocate(dataSize));

    // TODO: Replace hardcoded image format value
    frameProcessor->SetData(&data[_imageDataOffset], image, ImageFormat::Integer12);
    frameProcessor->Process();

	auto diffTime = std::chrono::high_resolution_clock::now() - start;
	auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

    std::string log = "BayerFramePreProcessor: " + std::to_string(frameTime) + "ms";
	OC_LOG_WARNING(log);


	image.SetRedChannel(frameProcessor->GetDataRed());
	image.SetGreenChannel(frameProcessor->GetDataGreen());
	image.SetBlueChannel(frameProcessor->GetDataBlue());
}
