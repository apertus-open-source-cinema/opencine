// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef RAWDUMP_H
#define RAWDUMP_H

#include <string>

namespace OC
{
    namespace Image
    {
        class RawDump
        {
        public:
            static bool Dump(std::string fileName, unsigned char* data, long length);
        };
    }
}

#endif //RAWDUMP_H
