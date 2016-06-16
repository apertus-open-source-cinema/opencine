#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <iostream>

#include "ImageDefines.h"

#include  "OCCore_export.h"

class IAllocator;

namespace OC
{
	namespace DataProvider
	{

		class OCImage;

		class OCCORE_EXPORT ImageProvider
		{
		public:
			bool ReadBinaryFile(std::string fileName, int& length, unsigned char*& fileData) const;
			void Load(std::string fileName, FileFormat format, OCImage& image, IAllocator& allocator) const;
		};
	}
}

#endif //IMAGEPROVIDER_H
