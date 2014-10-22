#ifndef IMAGEDATA_H
#define IMAGEDATA_H

class OCImage
{
  unsigned int _width;
  unsigned int _height;
  unsigned int _bytesPerPixel;

  void* _imageData;
  unsigned int _dataSize;
};

#endif //IMAGEDATA_H
