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

    // IDataProvider interface
public:
    OCFrame* LoadFile(std::string)
    {
        return nullptr;
    }

    OCFrame* LoadFolder(std::string)
    {
        return nullptr;
    }
};

#endif //TESTPLUGINA_H
