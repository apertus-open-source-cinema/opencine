#include "MLVLoader.h"

#include <algorithm>
#include <iostream>
#include <memory>

#include "EndianHelper.h"

#include "BayerFramePreProcessor.h"

using namespace OC::DataProvider;

mlv_file_hdr_t MLVLoader::ReadHeader(uint8_t* buffer, unsigned int& bufferPosition)
{
    mlv_file_hdr_t header;

    header.fileMagic = GetUInt32(&buffer[bufferPosition], bufferPosition);
    header.blockSize = GetUInt32(&buffer[bufferPosition], bufferPosition);
    std::copy(&buffer[bufferPosition], &buffer[bufferPosition + 8], header.versionString);
    bufferPosition += 8;
    header.fileGuid = GetUInt64(&buffer[bufferPosition], bufferPosition);
    header.fileNum = GetUInt16(&buffer[bufferPosition], bufferPosition);
    header.fileCount = GetUInt16(&buffer[bufferPosition], bufferPosition);
    header.fileFlags = GetUInt32(&buffer[bufferPosition], bufferPosition);
    header.videoClass = GetUInt16(&buffer[bufferPosition], bufferPosition);
    header.audioClass = GetUInt16(&buffer[bufferPosition], bufferPosition);
    header.videoFrameCount = GetUInt32(&buffer[bufferPosition], bufferPosition);
    header.audioFrameCount = GetUInt32(&buffer[bufferPosition], bufferPosition);
    header.sourceFpsNom = GetUInt32(&buffer[bufferPosition], bufferPosition);
    header.sourceFpsDenom = GetUInt32(&buffer[bufferPosition], bufferPosition);

    return header;
}

mlv_hdr_t MLVLoader::ReadBlockHeader(uint8_t* buffer, unsigned int& bufferPosition)
{
    mlv_hdr_t block;

    block.blockType = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.blockSize = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.timestamp = GetUInt64(&buffer[bufferPosition], bufferPosition);
    return block;
}

raw_info MLVLoader::ReadRawInfo(uint8_t* buffer, unsigned int& bufferPosition)
{
    raw_info block;

    block.api_version = GetUInt32(&buffer[bufferPosition], bufferPosition);
    //block.do_not_use_this = GetUInt32(&buffer[bufferPosition], bufferPosition);
    bufferPosition += 4; //step over some obsolete struct member
    block.height = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.width = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.pitch = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.frame_size = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.bits_per_pixel = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.black_level = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.white_level = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.crop.origin[0] = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.crop.origin[1] = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.crop.size[0] = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.crop.size[1] = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.active_area.y1 = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.active_area.x1 = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.active_area.y2 = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.active_area.x2 = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.exposure_bias[0] = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.exposure_bias[1] = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.cfa_pattern = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.calibration_illuminant1 = GetUInt32(&buffer[bufferPosition], bufferPosition);
    unsigned int tempLength = 18 * sizeof(int32_t);
    // TODO: Check the SIGABRT when the next line is active
    //std::copy(&buffer[bufferPosition], &buffer[bufferPosition] + tempLength, block.color_matrix1); // 4 * 18 -> uint32_t * 18
    bufferPosition += tempLength;
    block.dynamic_range = GetUInt32(&buffer[bufferPosition], bufferPosition);

    return block;
}

mlv_rawi_hdr_t MLVLoader::ReadRAWI(uint8_t* buffer, unsigned int& bufferPosition, mlv_hdr_t& /*blockHeader*/)
{
    mlv_rawi_hdr_t block;

    block.xRes = GetUInt16(&buffer[bufferPosition], bufferPosition);
    block.yRes = GetUInt16(&buffer[bufferPosition], bufferPosition);
    //block.rawInfo = &buffer[bufferPosition];
    block.rawInfo = ReadRawInfo(buffer, bufferPosition);

    return block;
}

mlv_vidf_hdr_t MLVLoader::ReadVIDF(uint8_t* buffer, unsigned int& bufferPosition, mlv_hdr_t& blockHeader)
{
    mlv_vidf_hdr_t block;

    block.frameNumber = GetUInt32(&buffer[bufferPosition], bufferPosition);
    block.cropPosX = GetUInt16(&buffer[bufferPosition], bufferPosition);
    block.cropPosY = GetUInt16(&buffer[bufferPosition], bufferPosition);
    block.panPosX = GetUInt16(&buffer[bufferPosition], bufferPosition);
    block.panPosY = GetUInt16(&buffer[bufferPosition], bufferPosition);
    block.frameSpace = GetUInt32(&buffer[bufferPosition], bufferPosition);
    //uint8_t	frameData

    // FIXME: Remove "processed" when frame loading is implemented, used here to get only first frame
    if(processed == false)
    {
        sourceData = &buffer[bufferPosition + block.frameSpace];
        processed = true;
    }

    bufferPosition += blockHeader.blockSize - (sizeof(mlv_vidf_hdr_t) + sizeof(mlv_hdr_t));

    return block;
}

MLVLoader::MLVLoader(uint8_t *data, unsigned size, OCImage& image, IAllocator& allocator)
{
    // TODO: Add handlng of endianess

    unsigned int bufferPosition = 0;
    mlv_file_hdr_t mlvHeader = ReadHeader(data, bufferPosition);

    unsigned int blockHeaderSize = sizeof(mlv_hdr_t);
    mlv_rawi_hdr_t blockRAWI;
    mlv_vidf_hdr_t blockVIDF;

    // TODO: Check if switch can be replaced by hash map of func<>
    while (bufferPosition < size)
    {
        mlv_hdr_t blockHeader = ReadBlockHeader(data, bufferPosition);
        switch (blockHeader.blockType)
        {
        case BlockType_RAWI:
        {
            blockRAWI = ReadRAWI(data, bufferPosition, blockHeader);
        }
            break;
        case BlockType_VIDF:
        {
            blockVIDF= ReadVIDF(data, bufferPosition, blockHeader);
        }
            break;
        case BlockType_NULL:
        {
            // Jump over this padding block
            bufferPosition += blockHeader.blockSize - blockHeaderSize;
        }
            break;
        default:
        {
            std::string s( reinterpret_cast<char const*>(&blockHeader.blockType), 4 ) ;
            std::cout << "No processing implemented for block. Type: " << s << " Size: " << blockHeader.blockSize <<" bytes"<<std::endl;

            // Jump over the block
            bufferPosition += blockHeader.blockSize - blockHeaderSize;
        }
        }
    }

    std::unique_ptr<BayerFramePreProcessor> frameProcessor(new BayerFramePreProcessor());

    // TODO: Add crop processing, currently full frame is taken
    unsigned int dataSize = blockRAWI.xRes * blockRAWI.yRes;
    image.SetWidth(blockRAWI.xRes);
    image.SetHeight(blockRAWI.yRes);
    image.SetBayerPattern(BayerPattern::RGGB);

    image.SetRedChannel(allocator.Allocate(dataSize));
    image.SetGreenChannel(allocator.Allocate(dataSize));
    image.SetBlueChannel(allocator.Allocate(dataSize));

    ImageFormat imageFormat = ImageFormat::Integer12;
    switch(blockRAWI.rawInfo.bits_per_pixel)
    {
    case 14:
        imageFormat = ImageFormat::Integer14;
        break;
    }

    frameProcessor->SetData(sourceData, image, imageFormat);
    //frameProcessor->SetLinearizationData(linearizationTable, linearizationLength);
    frameProcessor->Process();

    image.SetRedChannel(frameProcessor->GetDataRed());
    image.SetGreenChannel(frameProcessor->GetDataGreen());
    image.SetBlueChannel(frameProcessor->GetDataBlue());
}
