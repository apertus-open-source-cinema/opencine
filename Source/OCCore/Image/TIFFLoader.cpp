#include "TIFFLoader.h"

#include <memory>

#include "Log/ILogger.h"

#include "BayerFramePreProcessor.h"

using namespace OC::DataProvider;

unsigned char* imageData;

TIFFLoader::TIFFLoader(unsigned char* data, unsigned int size, OCImage& image) :
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

    tags  = new TIFFTag[_ifdEntries];
    memcpy(tags, data + header.IFDOffset + sizeof(_ifdEntries), sizeof(TIFFTag) * _ifdEntries);

    ImageFormat bitsPerPixel = ImageFormat::Integer12;
    std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
    ProcessTags(varMap, bitsPerPixel, size, image, data);

    for(int i = 0; i < _ifdEntries; i++)
    {
        if(_swapEndianess)
        {
            SwapTagEndianess(tags[i]);
        }

        std::cout << "Tag ID: " << tags[i].ID << std::endl;
        //LOG_WARNING("Tag ID: ");// << std::to_string(tags[i].ID));

        auto it = varMap.find(tags[i].ID);
        if(it != varMap.end())
        {
            (*it).second(tags[i]);
        }
    }

    PreProcess(data, image);

    Cleanup();
}

void TIFFLoader::Cleanup()
{
    if(imageData != nullptr)
    {
        delete[] imageData;
    }

    if(tags != nullptr)
    {
        delete[] tags;
    }
}

TIFFHeader TIFFLoader::ProcessHeader(char* buffer)
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

static int testOffset = 0;

void TIFFLoader::ProcessTags(std::unordered_map<int, std::function<void(TIFFTag&)>>& varMap, ImageFormat& bitsPerPixel, unsigned int size, OCImage& image, unsigned char* data)
{
    //std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
    varMap.insert(std::make_pair(256, [&image] (TIFFTag& tag) { image.SetWidth(tag.DataOffset); }));
    varMap.insert(std::make_pair(257, [&image] (TIFFTag& tag) { image.SetHeight(tag.DataOffset); }));
    varMap.insert(std::make_pair(33422, [&image] (TIFFTag& tag) //Bayer pattern
    {
                      image.SetType(ImageType::Bayer);
                      switch(tag.DataOffset)
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

    varMap.insert(std::make_pair(258, [&bitsPerPixel] (TIFFTag& tag)
    {
                      bitsPerPixel = static_cast<ImageFormat>(tag.DataOffset);
                  }));

    varMap.insert(std::make_pair(273, [&/*&data, &buffer, &width, &height, &bitsPerPixel*/] (TIFFTag& tag) mutable
    {
                      unsigned int size = (unsigned int)(image.Width() * image.Height() * ((float)bitsPerPixel / 8.0f));
                      imageData = new unsigned char[size];
                      testOffset = tag.DataOffset;
                      //memcpy(imageData, data + tag.DataOffset, size);
                      //image.SetData((unsigned char*)data + tag.DataOffset, size);
                  }));
}

void TIFFLoader::PreProcess(unsigned char* data, OCImage& image)
{
    std::unique_ptr<BayerFramePreProcessor> frameProcessor(new BayerFramePreProcessor());

    frameProcessor->SetData(data[testOffset], image.Width(), image.Height(), SourceFormat::Integer12, image.GetBayerPattern());

    frameProcessor->Process();

    image.SetRedChannel(frameProcessor->GetDataRed());
    image.SetGreenChannel(frameProcessor->GetDataGreen());
    image.SetBlueChannel(frameProcessor->GetDataBlue());
}
