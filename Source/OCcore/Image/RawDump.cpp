// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include <fstream>
#include <iostream>
#include "RawDump.h"
#include "Log/Logger.h"
using namespace OC::Image;

bool RawDump::dump(std::string fileName, unsigned char* data, long length){
    std::ofstream out;
    out.open(fileName, std::ios::binary);
    if (!out.is_open())
    {
        std::string err = "RawDump: File couldn't be opened: "+fileName;
        OC_LOG_ERROR(err);
        return false;
    }
    std::string begin = "RawDump: Begin dumping in: "+fileName;
    OC_LOG_INFO(begin);
    out.write((const char*)data,length);
    out.close();
    std::string end = "RawDump: Ended dumping in: "+fileName;
    OC_LOG_INFO(end);
    return true;
}
