#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <chrono>
#include <unordered_map>

#include <inttypes.h>

#include <unistd.h>

#include <memory>

//#include <API/IDataProvider.h>
#include <OCImage.h>

using namespace OC::DataProvider;

uint16_t ifdEntries;

enum class SourceFormat
{
    Integer12 = 12,
    Integer14 = 14
};

// Source: http://esr.ibiblio.org/?p=5095
static inline uint8_t IsBigEndianMachine()
{
    const uint16_t endianness = 256;
    return *(const uint8_t *)&endianness;
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

void SwapTagEndianess(TIFFTag& tag)
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

// TODO: Test
TIFFHeader ProcessHeader(char* buffer)
{
    TIFFHeader header;
    memcpy(&header, buffer, sizeof(TIFFHeader));
    SwapEndian(header.Version);
    SwapEndian(header.IFDOffset);

    return header;
}

int main()
{
    std::unique_ptr<OCImage> image(new OCImage());

    auto start = std::chrono::steady_clock::now();

    bool swapEndianess = false;

    std::ifstream is("Frame000338.dng", std::ifstream::binary);
    if(!is)
    {
        std::cout << "Error: File not found." << std::endl;
        return -1;
    }

    // get length of file:
    is.seekg(0, is.end);
    long length = is.tellg();
    is.seekg(0, is.beg);

    //char* buffer2 = new char[length];
    char* buffer = new char[length];

    // std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    is.read(buffer, length);
    // std::cout << "File loaded" << std::endl;

    if((buffer[0] << 8 | buffer[1]) == 0x4d4d && !IsBigEndianMachine())
    {
        swapEndianess = true;
    }

    TIFFHeader header = ProcessHeader(buffer);

    memcpy(&ifdEntries, buffer + header.IFDOffset, sizeof(ifdEntries));
    SwapEndian(ifdEntries);

    TIFFTag* tags = new TIFFTag[ifdEntries];
    memcpy(tags, buffer + header.IFDOffset + sizeof(ifdEntries), sizeof(TIFFTag) * ifdEntries);

    //int x = 3;
    //std::unordered_map<int, std::function<void()>> vM;
    //vM.insert(std::make_pair(1, [&x] () {x = 12;}));

    //auto it = vM.find(1);
    //it->second();

    //unsigned int width;
    //unsigned int height;
    SourceFormat bitsPerPixel;
    unsigned char* data = new unsigned char[1];

    std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
    varMap.insert(std::make_pair(256, [&image] (TIFFTag& tag) { image->SetWidth(tag.DataOffset); }));
    varMap.insert(std::make_pair(257, [&image] (TIFFTag& tag) { image->SetHeight(tag.DataOffset); }));
    varMap.insert(std::make_pair(258, [&bitsPerPixel] (TIFFTag& tag)
    {
        bitsPerPixel = static_cast<SourceFormat>(tag.DataOffset);
    }));
    varMap.insert(std::make_pair(273, [&/*&data, &buffer, &width, &height, &bitsPerPixel*/] (TIFFTag& tag) mutable
    {
        unsigned int size = (unsigned int)(image->Width() * image->Height() * ((float)bitsPerPixel / 8.0f));
        image->SetData((unsigned char*)buffer + tag.DataOffset, size);
    }));

    for(int i = 0; i < ifdEntries; i++)
    {
        SwapTagEndianess(tags[i]);

        std::cout << "Tag ID: " << tags[i].ID << std::endl;

        auto it = varMap.find(tags[i].ID);
        if(it != varMap.end())
        {
            (*it).second(tags[i]);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time: " << timeDiff.count() << "ms" << std::endl;

    delete[] tags;
    delete[] buffer;

    return 0;
}
