#include "LibRawDataProvider.h"

LibRawDataProvider::LibRawDataProvider()
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

bool LibRawDataProvider::LoadFile(IDataStorage* dataStorage, std::string filePath)
{
  OCFrame* frame = new OCFrame();

  // Creation of image processing object
  imageProcessor->open_file(filePath.c_str());
  imageProcessor->unpack();

  //imageProcessor.dcraw_process();
  //libraw_processed_image_t* rawImage = imageProcessor.dcraw_make_mem_image();

  //image->SetSize(rawImage->width, rawImage->height);
  //image->SetData(rawImage->data, rawImage->data_size);

  unsigned int width = imageProcessor->imgdata.rawdata.sizes.raw_width;
  unsigned int height = imageProcessor->imgdata.rawdata.sizes.raw_height;
  unsigned int pitch = imageProcessor->imgdata.rawdata.sizes.raw_pitch;

  unsigned short* imageData = nullptr;
  frame->SetSize(width, height);

  unsigned char bayerPattern[4];
  bayerPattern[0] = imageProcessor->COLOR(0,0);
  bayerPattern[1] = imageProcessor->COLOR(0,1);
  bayerPattern[2] = imageProcessor->COLOR(1,0);
  bayerPattern[3] = imageProcessor->COLOR(1,1);

  unsigned short* imageData2 = new unsigned short[width * height * 3];

  int size = width * height * 3 * sizeof(unsigned short);
  for(unsigned char& value : bayerPattern)
  {
    if(value == 3)
    {
      value = 1;
    }
  }

  imageData = new unsigned short[width * height];
  imageData2 = new unsigned short[width * height * 3];
  memcpy(imageData, imageProcessor->imgdata.rawdata.raw_image, pitch * height);

  unsigned int order = 0;
  bool checked = false;
  for(unsigned int y = 0; y < height; ++y)
  {
    checked = false;

    for(unsigned int x = 0; x < width; ++x)
    {
      int xOdd = x % 2;
      int yOdd = y % 2;

      if(yOdd)
      {
        xOdd += 2;
      }

      imageData2[((y * width + x) * 3) + bayerPattern[xOdd]] = imageData[y * width + x] * 3;
      /*if(y % 2 == 0)
        {

        }
        else
        {
          imageDataFloat[(((y * width) + x) * 3) + order] = 0;

          if(!checked)
          {
          cout << y << endl;
          checked = true;
          }
        }*/

      //      order++;
      //      if(order == 3)
      //      {
      //        order = 0;
      //      }
    }
  }

  frame->SetData(imageData2, width * height * 3 * sizeof(unsigned short));

  //imageProcessor.dcraw_clear_mem(rawImage);

  dataStorage->AddFrame(frame);

  return true;
}

OCFrame* LibRawDataProvider::LoadFolder(std::string folderPath)
{
  int i = 0;

  return nullptr;
}

std::string LibRawDataProvider::GetName()
{
  return "LibRaw data provider";
}

OCFrame* LibRawDataProvider::GetMetadataFromFile(std::string filePath)
{
  OCFrame* metaData = nullptr;

  imageProcessor->open_file(filePath.c_str());

  if(imageProcessor->imgdata.rawdata.sizes.width > 0)
  {
    metaData = new OCFrame();
    metaData->SetSize(imageProcessor->imgdata.rawdata.sizes.width, imageProcessor->imgdata.rawdata.sizes.height);
  }

  return metaData;
}
