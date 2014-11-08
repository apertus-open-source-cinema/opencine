#include "RawSpeedDataProvider.h"

//#include <RawSpeed/CameraMetaData.h>

//using namespace RawSpeed;

RawSpeedDataProvider::RawSpeedDataProvider() : IDataProvider(nullptr)
{
//    static CameraMetaData *metadata = NULL;
//    if (NULL == metadata)
//    {
//        try
//        {
//            metadata = new CameraMetaData("/home/andi/Source/OpenCine/3rdParty/RawSpeed/data");
//        }
//        catch (CameraMetadataException &e)
//        {
//            // Reading metadata failed. e.what() will contain error message.
//        }
//    }
}

RawSpeedDataProvider::~RawSpeedDataProvider()
{

}

OCImage* RawSpeedDataProvider::LoadFile(std::string filePath)
{
    OCImage* image = new OCImage();

    // Creation of image processing object
    //imageProcessor->open_file(filePath.c_str());
    //imageProcessor->unpack();
    //imageProcessor.dcraw_process();
    //libraw_processed_image_t* rawImage = imageProcessor.dcraw_make_mem_image();

    //image->SetSize(rawImage->width, rawImage->height);
    //image->SetData(rawImage->data, rawImage->data_size);

    //image->SetSize(imageProcessor->imgdata.rawdata.sizes.width, imageProcessor->imgdata.rawdata.sizes.height);
    //image->SetData(imageProcessor->imgdata.rawdata.raw_image, imageProcessor->imgdata.rawdata.sizes.raw_pitch * imageProcessor->imgdata.rawdata.sizes.height);

    //imageProcessor.dcraw_clear_mem(rawImage);

    return image;
}

OCImage *RawSpeedDataProvider::LoadFolder(std::string folderPath)
{

}

std::string RawSpeedDataProvider::GetName()
{
    return "RawSpeedDataProvider";
}
