#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <string.h>

class OCFrame
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

  void SetData(unsigned short* data, unsigned int dataSize)
  {
      _dataSize = dataSize;
      _imageData = new unsigned short[_dataSize];
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

  unsigned int GetSize()
  {
      return _dataSize;
  }
};

#endif //IMAGEDATA_H
