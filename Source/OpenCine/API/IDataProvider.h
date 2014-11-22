#ifndef IDATAPROVIDER_H
#define IDATAPROVIDER_H

#include "IPlugin.h"

#include <string>

#include "../Core/ImageData.h"
#include "../API/IDataStorage.h"

namespace OpenCineAPI
{
  class IDataProvider : public IPlugin
  {
    IDataStorage* _dataStorage;

  public:
    IDataProvider(IDataStorage* dataStorage) : _dataStorage(dataStorage) {}

    virtual OCImage* LoadFile(std::string) = 0;
    virtual OCImage* LoadFolder(std::string) = 0;

    virtual OCImage* GetMetadataFromFile(std::string) = 0;
  };
}

#endif //IDATAPROVIDER_H
