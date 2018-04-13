//
// Created by supragya on 13/4/18.
//

#include <fstream>
#include <iostream>
#include "rawdump.h"
#include "Log/Logger.h"

bool OcRawDump::dump(std::string fileName, unsigned char* data, long length){
    std::ofstream os;
    os.open(fileName, std::ios::binary);
    if (!os.is_open())
    {
        std::string err = "OcRawDump: File couldn't be opened: ";
        err.append(fileName);
        OC_LOG_ERROR(err);
        return false;
    }
    std::string begin = "OcRawDump: Begin dumping in: ";
    begin.append(fileName);
    OC_LOG_INFO(begin);
    os.write((const char*)data,length);
    os.close();
    std::string end = "OcRawDump: Ended dumping in: ";
    end.append(fileName);
    OC_LOG_INFO(end);
    return true;
}
