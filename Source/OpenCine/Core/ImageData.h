#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <string.h>

class OCImage
{
  unsigned int _width;
  unsigned int _height;
  unsigned int _bytesPerPixel;

  void* _imageData;
  unsigned int _dataSize;

public:
  void SetSize(unsigned int width, unsigned int height)
  {
      _width = width;
      _height = height;
  }

  void SetData(unsigned char* data, unsigned int dataSize)
  {
      _dataSize = dataSize;
      _imageData = new unsigned char[_dataSize];
      memcpy(_imageData, data, _dataSize);
  }

  unsigned int GetWidth()
  {
      return _width;
  }

  unsigned int GetHeight()
  {
      return _height;
  }

  void* GetData()
  {
      return _imageData;
  }
};

#endif //IMAGEDATA_H
