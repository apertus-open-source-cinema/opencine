#include "LibRawDataProvider.h"

LibRawDataProvider::LibRawDataProvider() : IDataProvider(nullptr)
{
  imageProcessor = new LibRaw();
}

LibRawDataProvider::~LibRawDataProvider()
{
  if(imageProcessor != nullptr)
  {
    delete imageProcessor;
  }
}

OCImage* LibRawDataProvider::LoadFile(std::string filePath)
{
    OCImage* image = new OCImage();

    // Creation of image processing object
    imageProcessor->open_file(filePath.c_str());
    imageProcessor->unpack();
    //imageProcessor.dcraw_process();
    //libraw_processed_image_t* rawImage = imageProcessor.dcraw_make_mem_image();

    //image->SetSize(rawImage->width, rawImage->height);
    //image->SetData(rawImage->data, rawImage->data_size);

    image->SetSize(imageProcessor->imgdata.rawdata.sizes.width, imageProcessor->imgdata.rawdata.sizes.height);
    image->SetData(imageProcessor->imgdata.rawdata.raw_image, imageProcessor->imgdata.rawdata.sizes.raw_pitch * imageProcessor->imgdata.rawdata.sizes.height);

    //imageProcessor.dcraw_clear_mem(rawImage);

    return image;
}

OCImage* LibRawDataProvider::LoadFolder(std::string folderPath)
{
    int i = 0;
}

std::string LibRawDataProvider::GetName()
{
  return "LibRaw data provider";
}

OCImage* LibRawDataProvider::GetMetadataFromFile(std::string filePath)
{
  OCImage* metaData = nullptr;

  imageProcessor->open_file(filePath.c_str());

  if(imageProcessor->imgdata.rawdata.sizes.width > 0)
  {
    metaData = new OCImage();
    metaData->SetSize(imageProcessor->imgdata.rawdata.sizes.width, imageProcessor->imgdata.rawdata.sizes.height);
  }

  return metaData;
}
