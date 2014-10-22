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

OCImage* LibRawDataProvider::LoadFile(std::string)
{

}

OCImage* LibRawDataProvider::LoadFolder(std::string)
{

}

std::string LibRawDataProvider::GetName()
{
    return "LibRaw data provider";
}
