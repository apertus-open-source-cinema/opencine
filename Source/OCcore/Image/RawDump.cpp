// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "RawDump.h"

#include <fstream>
#include <iostream>

#include <lodepng/lodepng.h>

#include "Log/Logger.h"
#include "OCImage.h"

using namespace OC::Image;

bool RawDump::Dump(std::string fileName, unsigned char *data, long length)
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

    out.write((const char *)data, length);
    out.close();

    std::string end = "RawDump: Ended dumping in: " + fileName;
    OC_LOG_INFO(end);

    return true;
}

bool RawDump::DumpPNG(std::string fileName, OCImage &image)
{
    unsigned int dataLength = image.Width() * image.Height();
    unsigned char *interleavedArray = new unsigned char[dataLength * 3];

    uint16_t *redArray = static_cast<uint16_t *>(image.RedChannel());
    uint16_t *greenArray = static_cast<uint16_t *>(image.GreenChannel());
    uint16_t *blueArray = static_cast<uint16_t *>(image.BlueChannel());

    for(unsigned int i = 0; i < dataLength; i++)
    {
        interleavedArray[i * 3] = static_cast<uint8_t>(redArray[i] >> 4);
        interleavedArray[i * 3 + 1] = static_cast<uint8_t>(greenArray[i] >> 4);
        interleavedArray[i * 3 + 2] = static_cast<uint8_t>(blueArray[i] >> 4);
    }

    lodepng::encode(fileName, interleavedArray, image.Width(), image.Height(), LCT_RGB);
}
