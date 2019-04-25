// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "RawDump.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include <lodepng/lodepng.h>

#include "Log/Logger.h"
#include "OCImage.h"

using namespace OC::Image;

bool RawDump::DumpRAW(std::string fileName, uint8_t* data, long length)
{
    std::ofstream out(fileName, std::ios::binary);
    if(!out.is_open())
    {
        std::string err = "RawDump: File couldn't be opened: " + fileName;
        OC_LOG_ERROR(err);
        return false;
    }

    std::string begin = "RawDump: Begin dumping in: " + fileName;
    OC_LOG_INFO(begin);

    out.write(reinterpret_cast<char*>(data), length);
    out.close();

    std::string end = "RawDump: Ended dumping in: " + fileName;
    OC_LOG_INFO(end);

    return true;
}

uint8_t RawDump::GetBitShift(OCImage& image)
{
    uint8_t offset = 0;

    switch(image.Format())
    {
        case ImageFormat::Integer12:
            offset = 4;
            break;
        case ImageFormat::Integer14:
            offset = 6;
            break;
        case ImageFormat::Integer16:
            offset = 8;
            break;
        default:
            break;
    }

    return offset;
}

bool EndsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool RawDump::DumpPNG(std::string fileName, OCImage& image)
{
    uint16_t* redArray = static_cast<uint16_t*>(image.RedChannel());
    uint16_t* greenArray = static_cast<uint16_t*>(image.GreenChannel());
    uint16_t* blueArray = static_cast<uint16_t*>(image.BlueChannel());

    // Defines conversion to 8 bits from image data

    uint8_t offset = GetBitShift(image);

    unsigned int dataLength = image.Width() * image.Height();
    unsigned char* interleavedArray = new unsigned char[dataLength * 3];
    for(unsigned int i = 0; i < dataLength; i++)
    {
        interleavedArray[i * 3] = static_cast<uint8_t>(redArray[i] >> offset);
        interleavedArray[i * 3 + 1] = static_cast<uint8_t>(greenArray[i] >> offset);
        interleavedArray[i * 3 + 2] = static_cast<uint8_t>(blueArray[i] >> offset);
    }

    size_t lastDotIndex = fileName.find_last_of(".");
    std::string extension = "";
    if(lastDotIndex != std::string::npos)
    {
        extension = fileName.substr(fileName.find_last_of("."));
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    }

    if(!EndsWith(extension, ".png"))
    {
        fileName += ".png";
    }

    unsigned int result = lodepng::encode(fileName, interleavedArray, image.Width(), image.Height(), LCT_RGB);
    if(result != 0)
    {
        OC_LOG_ERROR(lodepng_error_text(result));
        return false;
    }

    return true;
}
