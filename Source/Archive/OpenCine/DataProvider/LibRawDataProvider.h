#ifndef LIBRAWDATAPROVIDER_H
#define LIBRAWDATAPROVIDER_H

//General includes
#include <memory>

//OpenCineAPI includes
#include "API/IDataProvider.h"
#include "API/IDataStorage.h"
#include "Core/ImageData.h"

//LibRaw includes
#include <libraw/libraw.h>

using namespace OpenCineAPI;

class LibRawDataProvider : public IDataProvider
{
    LibRaw* imageProcessor;

public:
    LibRawDataProvider();
    ~LibRawDataProvider();

    // IDataProvider interface
    bool LoadFile(IDataStorage* dataStorage, std::string filePath);
    OCFrame* LoadFolder(std::string folderPath);

    // IPlugin interface
    std::string GetName();

    OCFrame* GetMetadataFromFile(std::string filePath);

    // IPlugin interface
public:
    void Initialize() {}

    // IDataProvider interface
public:
    bool ScanFolder(std::vector<ClipInfo> &foundData) {return false;}
};

#endif //LIBRAWDATAPROVIDER_H
