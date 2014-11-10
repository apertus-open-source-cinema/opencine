#ifndef RAWSPEEDDATAPROVIDER_H
#define RAWSPEEDDATAPROVIDER_H

//General includes
#include <memory>

//OpenCineAPI includes
#include "../API/IDataProvider.h"

using namespace OpenCineAPI;

class RawSpeedDataProvider : public IDataProvider
{
    //LibRaw* imageProcessor;

public:
    RawSpeedDataProvider();
    ~RawSpeedDataProvider();

    // IDataProvider interface
    OCImage* LoadFile(std::string filePath);
    OCImage* LoadFolder(std::string folderPath);

    // IPlugin interface
    std::string GetName();
};

#endif //RAWSPEEDDATAPROVIDER_H
