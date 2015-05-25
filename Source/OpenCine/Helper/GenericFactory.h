#ifndef GENERICFACTORY_H
#define GENERICFACTORY_H

#include <vector>
#include <functional>

template<class BaseType> class GenericFactory
{
public:
  ~GenericFactory()
  {
    for(auto element : registeredDataProviders)
    {
      delete element;
    }
  }

  template <class T>
  void Register()
  {
    try
    {
      //std::function<T*()> func = nullptr;
      std::function<BaseType*()> func = []() { return new T(); };
      registeredDataProviders.push_back(func);
    }
    catch(std::exception e)
    {
    }
  }

  BaseType* Get(unsigned int pluginID)
  {
    try
    {
      auto func = registeredDataProviders.at(pluginID);
      //std::function<BaseType*()>
      //if (it != registeredDataProviders.end())
      //{
      if(func != nullptr)
      {
        return func();
      }
    }
    catch(std::exception& e)
    {
      return nullptr;
    }

    return nullptr;
  }

  std::vector<std::function<BaseType*()>> GetList()
  {
    return registeredDataProviders;
  }

private:
  std::vector<std::function<BaseType*()>> registeredDataProviders;
};

#endif //GENERICFACTORY_H
