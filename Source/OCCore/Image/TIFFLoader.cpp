#include "TIFFLoader.h"

#include <memory>

#include "BayerFrameProcessor.h"

using namespace OC::DataProvider;

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

    TIFFTag* tags = new TIFFTag[_ifdEntries];
    memcpy(tags, data + header.IFDOffset + sizeof(_ifdEntries), sizeof(TIFFTag) * _ifdEntries);

    ImageFormat bitsPerPixel = ImageFormat::Integer12;
    std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
    ProcessTags(varMap, bitsPerPixel, size, image);

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

    PreProcess(data, image);
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

void TIFFLoader::ProcessTags(std::unordered_map<int, std::function<void(TIFFTag&)>>& varMap, ImageFormat& bitsPerPixel, unsigned int size, OCImage& image)
{
    //std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
    varMap.insert(std::make_pair(256, [&image] (TIFFTag& tag) { image.SetWidth(tag.DataOffset); }));
    varMap.insert(std::make_pair(257, [&image] (TIFFTag& tag) { image.SetHeight(tag.DataOffset); }));
    varMap.insert(std::make_pair(33422, [&image] (TIFFTag& tag) { image.SetType(ImageType::Bayer); }));

    varMap.insert(std::make_pair(258, [&bitsPerPixel] (TIFFTag& tag)
    {
                      bitsPerPixel = static_cast<ImageFormat>(tag.DataOffset);
                  }));

    varMap.insert(std::make_pair(273, [&/*&data, &buffer, &width, &height, &bitsPerPixel*/] (TIFFTag& tag) mutable
    {
                      unsigned int size = (unsigned int)(image.Width() * image.Height() * ((float)bitsPerPixel / 8.0f));
                      //image.SetData((unsigned char*)data + tag.DataOffset, size);
                  }));
}

void TIFFLoader::PreProcess(unsigned char* data, OCImage& image)
{
    std::unique_ptr<IFrameProcessor> frameProcessor(new BayerFrameProcessor());

    frameProcessor->SetData(*data, image.Width(), image.Height(), SourceFormat::Integer12);

    frameProcessor->Process();

    image.SetRedChannel(frameProcessor->GetDataRed());
    image.SetGreenChannel(frameProcessor->GetDataGreen());
    image.SetBlueChannel(frameProcessor->GetDataBlue());
}
