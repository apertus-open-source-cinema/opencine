// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef MLVLOADER_H
#define MLVLOADER_H

#include <vector>

#include <Memory/StaticAllocator.h>

#include "IImageLoader.h"

#include "OCImage.h"

#include "mlv_structure_mod.h"

namespace OC
{
    namespace DataProvider
    {
        // NOTE: right to left, eg. BlockType_RAWI 0x49574152 -> IWAR
        #define BlockType_RAWI 0x49574152
        #define BlockType_VIDF 0x46444956
        #define BlockType_NULL 0x4c4c554e

        class MLVLoader : public IImageLoader
        {
            // FIXME: Just a temporary variable, remove after succesful tests
            bool processed = false;

            uint16_t* targetData;
            uint8_t* sourceData;

            mlv_file_hdr_t ReadHeader(uint8_t* buffer, unsigned int& bufferPosition);
            mlv_hdr_t ReadBlockHeader(uint8_t* buffer, unsigned int& bufferPosition);
            mlv_rawi_hdr_t ReadRAWI(uint8_t* buffer, unsigned int& bufferPosition, mlv_hdr_t& /*blockHeader*/);
            raw_info ReadRawInfo(uint8_t* buffer, unsigned int& bufferPosition);
            mlv_vidf_hdr_t ReadVIDF(uint8_t* buffer, unsigned int& bufferPosition, mlv_hdr_t& blockHeader);
            void Convert14To16Bit(uint8_t* source, uint16_t* target, long length);

        public:
            MLVLoader();

            void Load(uint8_t* data, unsigned size, OCImage &image, IAllocator &allocator) override;
        };
    }
}
#endif //MLVLOADER_H
