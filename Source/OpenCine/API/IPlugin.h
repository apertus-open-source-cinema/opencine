#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <string>

namespace OpenCineAPI
{
  class IPlugin
  {
      std::string _pluginName;

    protected:
      IPlugin(std::string pluginName) :
      _pluginName(pluginName)
      {
      }

    public:
      virtual ~IPlugin()
      {
      }

      virtual void Initialize() = 0;

      std::string GetName()
      {
        return _pluginName;
      }
  };
}

#endif //IPLUGIN_H
