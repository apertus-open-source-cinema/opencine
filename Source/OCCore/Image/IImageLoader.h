#ifndef IIMAGELOADER_H
#define IIMAGELOADER_H

#include "OCImage.h"
#include "Memory/StaticAllocator.h"

namespace OC
{
    namespace DataProvider
    {
        // TODO: Add base methods
        class IImageLoader
        {
        public:
            virtual void Load(uint8_t* data, unsigned int size, OCImage& image, IAllocator& allocator) = 0;
        };
    }
}
#endif //IIMAGELOADER_H
