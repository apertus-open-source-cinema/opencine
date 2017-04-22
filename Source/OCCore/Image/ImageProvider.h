#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "ImageDefines.h"

#include  "OCCore_export.h"

class IAllocator;

namespace OC
{
	namespace DataProvider
	{
		class OCImage;
        class IImageLoader;

		class OCCORE_EXPORT ImageProvider
		{
            // FIXME: Evaluate usage of FileFormat enum as key
            std::unordered_map<FileFormat, std::shared_ptr<IImageLoader>, FileFormatHash> _imageProviders;

		public:
            ImageProvider();

			bool ReadBinaryFile(std::string fileName, int& length, unsigned char*& fileData) const;
			void Load(std::string fileName, FileFormat format, OCImage& image, IAllocator& allocator) const;
		};
	}
}

#endif //IMAGEPROVIDER_H
