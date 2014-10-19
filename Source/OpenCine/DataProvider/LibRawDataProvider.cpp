#include "LibRawDataProvider.h"

LibRawDataProvider::LibRawDataProvider(IDataStorage* dataStorage) : IDataProvider(dataStorage)
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

ImageData* LibRawDataProvider::LoadFile(std::string)
{

}

ImageData* LibRawDataProvider::LoadFolder(std::string)
{

}

std::string LibRawDataProvider::GetName()
{
    return "LibRaw data provider";
}
