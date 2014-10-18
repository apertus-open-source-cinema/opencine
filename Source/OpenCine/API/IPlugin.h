#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <string>

namespace OpenCineAPI
{
  class IPlugin
  {
        virtual std::string GetName() = 0;
  };
}

#endif //IPLUGIN_H
