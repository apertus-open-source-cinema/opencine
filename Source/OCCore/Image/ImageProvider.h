#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <chrono>
#include <fstream>

#include <Log/ILogger.h>

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
				auto start = std::chrono::high_resolution_clock::now();

				std::ifstream is;
				is.open(fileName, std::ios::binary);

				if (!is.is_open())
				{
					std::cout << "ImageProvider: File couldn't be opened" << std::endl;
					return;
				}

				// get length of file:
				is.seekg(0, std::ios::end);
				length = is.tellg();
				is.seekg(0, std::ios::beg);

				// allocate memory:
				unsigned char* imageData = new unsigned char[length];

				// read data as a block:
				is.read((char*)imageData, length);
				is.close();

				auto diffTime = std::chrono::high_resolution_clock::now() - start;
				auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

				std::string log = "File loading: " + std::to_string(frameTime) + "ms";
				//OC_LOG_INFO(log);

				start = std::chrono::high_resolution_clock::now();
				IImageLoader* imageLoader = nullptr;
				if (format == FileFormat::DNG)
				{
					imageLoader = new TIFFLoader(imageData, length, image);
				}

				diffTime = std::chrono::high_resolution_clock::now() - start;
				frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

				log = "File processing: " + std::to_string(frameTime) + "ms";
				//OC_LOG_INFO(log);

				delete imageLoader;

				delete[] imageData;
			}
		};
	}
}

#endif //IMAGEPROVIDER_H
