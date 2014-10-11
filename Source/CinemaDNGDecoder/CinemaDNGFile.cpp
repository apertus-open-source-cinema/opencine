#include "CinemaDNGFile.h"

CinemaDNGFile::CinemaDNGFile() :
_width(0),
_height(0)
{
}

void CinemaDNGFile::SetWidth(int width)
{
  _width = width;
}

int CinemaDNGFile::GetWidth()
{
  return _width;
}

void CinemaDNGFile::SetHeight(int height)
{
  _height = height;
}

int CinemaDNGFile::GetHeight()
{
  return _height;
}
