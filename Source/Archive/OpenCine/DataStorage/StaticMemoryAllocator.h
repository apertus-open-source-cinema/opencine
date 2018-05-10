#ifndef STATICMEMORYALLOCATOR_H
#define STATICMEMORYALLOCATOR_H

#include "../API/IDataStorage.h"

#include "../API/IDataProvider.h"
#include "../Core/ImageData.h"
#include <vector>

using namespace OpenCineAPI;

class StaticMemoryAllocator : public IDataStorage
{
    //std::vector<OCFrame*> _frameList;
    //IDataProvider* _dataProvider;

    // IDataStorage interface
public:
    StaticMemoryAllocator();

    //bool ImportFolder(std::string folderPath);

    unsigned int GetFrameCount();

    void AddFrame(OCFrame* frame);
    OCFrame* GetFrame(unsigned int frameNumber);

    // IDataStorage interface
};

#endif //STATICMEMORYALLOCATOR_H
