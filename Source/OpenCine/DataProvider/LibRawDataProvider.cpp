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
    LibRaw imageProcessor;
    imageProcessor.open_file(filePath.c_str());
    imageProcessor.unpack();
    imageProcessor.dcraw_process();
    libraw_processed_image_t* rawImage = imageProcessor.dcraw_make_mem_image();

    image->SetSize(rawImage->width, rawImage->height);
    image->SetData(rawImage->data, rawImage->data_size);

    imageProcessor.dcraw_clear_mem(rawImage);

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
