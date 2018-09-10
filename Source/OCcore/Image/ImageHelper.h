// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H

#include <inttypes.h>

namespace OC
{
    namespace Image
    {
        namespace ImageHelper
        {
            inline void Convert12To16Bit(uint8_t* inputData, unsigned int width, unsigned int height, uint16_t* outputData)
            {
                unsigned int size = width * height;
                int j = 0;
                int dataSize = static_cast<int>(size * 1.5f); //12bit / 8bit

                //Take every 3 bytes to extract 2 x 12bits
                for (long long index = 0; index < dataSize; index += 3)
                {
                    uint32_t mergedBytes = (static_cast<uint32_t>(inputData[index + 0]) << 16) +
                            (static_cast<uint32_t>(inputData[index + 1]) << 8) +
                            static_cast<uint32_t>(inputData[index + 2]);

                    outputData[j + 1] = static_cast<uint16_t>(mergedBytes & 0xFFF);
                    outputData[j] = static_cast<uint16_t>((mergedBytes >> 12) & 0xFFF);

                    j += 2;
                }
            }

            inline void Convert14To16Bit(uint8_t* inputData, unsigned int width, unsigned int height, uint16_t* outputData)
            {
                int j = 0;
                int dataSize = static_cast<int>((width * 1.75) * height); // 14bit / 8bit

                // Process 8 bytes at once to get 4 pixels of 14 bits
                //#pragma omp parallel for
                for (long index = 0; index < dataSize; index += 14)
                {
                    uint64_t mergedBytes1 = (static_cast<uint64_t>(inputData[index]) << 56) +
                            (static_cast<uint64_t>(inputData[index + 1]) << 48) +
                            (static_cast<uint64_t>(inputData[index + 2]) << 40) +
                            (static_cast<uint64_t>(inputData[index + 3]) << 32) +
                            (static_cast<uint64_t>(inputData[index + 4]) << 24) +
                            (static_cast<uint64_t>(inputData[index + 5]) << 16) +
                            (static_cast<uint64_t>(inputData[index + 6]) << 8) +
                            static_cast<uint64_t>(inputData[index + 7]);

                    uint64_t mergedBytes2 = (static_cast<uint64_t>(inputData[index + 8]) << 40) +
                            (static_cast<uint64_t>(inputData[index + 9]) << 32) +
                            (static_cast<uint64_t>(inputData[index + 10]) << 24) +
                            (static_cast<uint64_t>(inputData[index + 11]) << 16) +
                            (static_cast<uint64_t>(inputData[index + 12]) << 8) +
                            static_cast<uint64_t>(inputData[index + 13]);

                    // Processing bytes in reversed order, so it resembles the shifting of uint64_t to the right
                    outputData[j + 7] = static_cast<uint16_t>(mergedBytes2 & 0x3FFF);
                    outputData[j + 6] = static_cast<uint16_t>((mergedBytes2 >> 14) & 0x3FFF);
                    outputData[j + 5] = static_cast<uint16_t>((mergedBytes2 >> 28) & 0x3FFF);
                    outputData[j + 4] = static_cast<uint16_t>((mergedBytes1 << 6) & 0x3FC0) + static_cast<uint16_t>((mergedBytes2 >> 42) & 0x3F);

                    // Offset: 6 bits
                    outputData[j + 3] = static_cast<uint16_t>(mergedBytes1 >> 8) & 0x3FFF;
                    outputData[j + 2] = static_cast<uint16_t>(mergedBytes1 >> 22) & 0x3FFF;
                    outputData[j + 1] = static_cast<uint16_t>(mergedBytes1 >> 36) & 0x3FFF;
                    outputData[j] = static_cast<uint16_t>(mergedBytes1 >> 50) & 0x3FFF;

                    j += 8;
                }
            }
        }
    }
}

#endif //IMAGEHELPER_H
