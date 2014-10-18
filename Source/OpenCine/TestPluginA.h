#ifndef TESTPLUGINA_H
#define TESTPLUGINA_H

#include "API/IDataProvider.h"

using namespace OpenCineAPI;

class TestPluginA : public IDataProvider
{
public:
    std::string GetName()
    {
        return "Test plugin A";
    }
};

#endif //TESTPLUGINA_H
