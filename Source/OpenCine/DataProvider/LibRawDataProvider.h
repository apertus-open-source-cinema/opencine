#ifndef LIBRAWDATAPROVIDER_H
#define LIBRAWDATAPROVIDER_H

#include "LibRawDataProvider.h"

//General includes
#include <memory>

//OpenCineAPI includes
#include "../API/IDataProvider.h"

//LibRaw includes
#include <libraw/libraw.h>

using namespace OpenCineAPI;

class LibRawDataProvider : public IDataProvider
{
    LibRaw* imageProcessor;

public:
    LibRawDataProvider(IDataStorage* dataStorage);
    ~LibRawDataProvider();

    // IDataProvider interface
    ImageData* LoadFile(std::string);
    ImageData* LoadFolder(std::string);

    // IPlugin interface
    std::string GetName();
};

#endif //LIBRAWDATAPROVIDER_H
