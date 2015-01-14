#ifndef LIBRAWTEST
#define LIBRAWTEST

//LibRaw includes
#include "/home/andi/Source/OpenCine/3rdParty/LibRaw/libraw/libraw.h"

unsigned short* imageData = nullptr;
unsigned short* imageDataFloat = nullptr;

void LibRawTest()
{
  LibRaw imageProcessor;
  imageProcessor.open_file("000100.dng");
  imageProcessor.unpack();

  unsigned int width = imageProcessor.imgdata.rawdata.sizes.raw_width;
  unsigned int height = imageProcessor.imgdata.rawdata.sizes.height;
  unsigned int pitch = imageProcessor.imgdata.rawdata.sizes.raw_pitch;

  unsigned int bitDepth = imageProcessor.imgdata.color.maximum;

  imageData = new unsigned short[width * height];

  memcpy(imageData, imageProcessor.imgdata.rawdata.raw_image, pitch * height);

  int first_visible_pixel = imageProcessor.imgdata.sizes.raw_width * imageProcessor.imgdata.sizes.top_margin + imageProcessor.imgdata.sizes.left_margin;

  unsigned char bayerPattern[4];
  bayerPattern[0] = imageProcessor.COLOR(0,0);
  bayerPattern[1] = imageProcessor.COLOR(0,1);
  bayerPattern[2] = imageProcessor.COLOR(1,0);
  bayerPattern[3] = imageProcessor.COLOR(1,1);

  for(unsigned char& value : bayerPattern)
  {
    if(value == 3)
    {
      value = 1;
    }
  }

  imageDataFloat = new unsigned short[width * height * 3];
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

      imageDataFloat[((y * width + x) * 3) + bayerPattern[xOdd]] = imageData[y * width + x] * 3;
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
}

#endif // LIBRAWTEST

