#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <fstream>

#include "TIFFLoader.h"

namespace OC
{
    namespace DataProvider
    {
        class ImageProvider
        {
        public:
            void Load(std::string fileName, FileFormat format, OCImage& image)
            {
                int length;

                std::ifstream is;
                is.open (fileName, std::ios::binary );

                if(!is.is_open())
                {
                    std::cout << "ImageProvider: File couldn't be opened" << std::endl;
                    return;
                }

                // get length of file:
                is.seekg (0, std::ios::end);
                length = is.tellg();
                is.seekg (0, std::ios::beg);

                // allocate memory:
                unsigned char* imageData = new unsigned char [length];

                // read data as a block:
                is.read ((char*)imageData,length);
                is.close();

                IImageLoader* imageLoader = nullptr;
                if(format == FileFormat::DNG)
                {
                    imageLoader = new TIFFLoader(imageData, length, image);
                }
            }
        };
    }
}

#endif //IMAGEPROVIDER_H

