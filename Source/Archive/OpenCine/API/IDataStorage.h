#ifndef IDATASTORAGE_H
#define IDATASTORAGE_H

#include <string>
#include <vector>

#include "../Core/ImageData.h"

namespace OpenCineAPI
{
    class IDataStorage
    {
    protected:
        std::vector<OCFrame*> _frameList;

    public:
        //virtual bool ImportFolder(std::string folderPath) = 0;

        virtual unsigned int GetFrameCount() = 0;

        virtual void AddFrame(OCFrame*) = 0;
        virtual OCFrame* GetFrame(unsigned int frameNumber) = 0;
    };
}

#endif //IDATASTORAGE_H
