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

    }

    OCFrame* LoadFolder(std::string)
    {

    }
};

#endif //TESTPLUGINA_H
