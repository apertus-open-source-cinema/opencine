#ifndef IDATAPROVIDER_H
#define IDATAPROVIDER_H

#include "IPlugin.h"

#include <string>
#include <map>
#include <functional>

#include "../Core/ImageData.h"
#include "../API/IDataStorage.h"

enum class ClipType : unsigned int
{
  DNG,
  MXF,
  MOX,
  DPX,
  MLV
};

namespace OpenCineAPI
{
  class IDataProvider : public IPlugin
  {
    IDataStorage* _dataStorage;

  public:
    IDataProvider(IDataStorage* dataStorage) : _dataStorage(dataStorage) {}

    virtual OCFrame* LoadFile(std::string) = 0;
    virtual OCFrame* LoadFolder(std::string) = 0;

    virtual OCFrame* GetMetadataFromFile(std::string) = 0;
  };

  /*class DataProviderFactory
  {
  public:
      template <typename T>
      void Register(const char* name)
      {
          _dataProviderList[name] = &CreateFunc<T>;
      }

  private:
      template <typename T>
      static IDataProvider* CreateFunc()
      {
          return new T;
      }

  private:
      typedef IDataProvider* (*CreateFunction)();
      std::map<std::string,CreateFunction> _dataProviderList;
  };*/

  class DataProviderFactory
  {
  public:
    template <typename T>
    void Register(ClipType type)
    {
      std::function<IDataProvider*()> func = []() { return new T; };
      registeredDataProviders.emplace(std::make_pair(type, func));
    }

    IDataProvider* Get(ClipType type)
    {
      std::map<ClipType, std::function<IDataProvider*()>>::iterator it = registeredDataProviders.find(type);

      if (it != registeredDataProviders.end())
      {
        return (*it).second();
      }

      return nullptr;
    }

  private:
    std::map<ClipType, std::function<IDataProvider*()>> registeredDataProviders;
  };
}


#endif //IDATAPROVIDER_H
