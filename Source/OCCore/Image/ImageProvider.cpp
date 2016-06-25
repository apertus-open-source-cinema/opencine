#include "ImageProvider.h"

#include <chrono>
#include <string>

#include "Log/Logger.h"
#include "IImageLoader.h"
#include "TIFFLoader.h"

using namespace OC::DataProvider;

bool ImageProvider::ReadBinaryFile(std::string fileName, int& length, unsigned char*& fileData) const
{
	std::ifstream is;
	is.open(fileName, std::ios::binary);

	if (!is.is_open())
	{
		std::cout << "ImageProvider: File couldn't be opened" << std::endl;
		return true;
	}

	// get length of file:
	is.seekg(0, std::ios::end);
	length = is.tellg();
	is.seekg(0, std::ios::beg);

	// allocate memory:
	fileData = new unsigned char[length];

	// read data as a block:
	is.read(reinterpret_cast<char*>(fileData), length);
	is.close();
	return false;
}

void ImageProvider::Load(std::string fileName, FileFormat format, OCImage& image, IAllocator& allocator) const
{
	int length = -1;
	unsigned char* fileData = nullptr;

	auto start = std::chrono::high_resolution_clock::now();

	if (ReadBinaryFile(fileName, length, fileData)) return;

	auto diffTime = std::chrono::high_resolution_clock::now() - start;
	auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

	auto log = "File loading: " + std::to_string(frameTime) + "ms";
	OC_LOG_INFO(log);

	start = std::chrono::high_resolution_clock::now();
	IImageLoader* imageLoader = nullptr;
	if (format == FileFormat::DNG)
	{
		imageLoader = new TIFFLoader(fileData, length, image, allocator);
	}

	diffTime = std::chrono::high_resolution_clock::now() - start;
	frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

	log = "File processing: " + std::to_string(frameTime) + "ms";
	OC_LOG_INFO(log);

	delete imageLoader;

	delete [] fileData;
}
