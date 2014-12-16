#ifndef IDATASTORAGE_H
#define IDATASTORAGE_H

#include <ImageData.h>
#include <string>

namespace OpenCineAPI
{
    class IDataStorage
    {
    public:
        virtual bool ImportFolder(std::string folderPath) = 0;

        virtual unsigned int GetFrameCount() = 0;
        virtual OCFrame* GetFrame(unsigned int frameNumber) = 0;
    };
}

#endif //IDATASTORAGE_H
