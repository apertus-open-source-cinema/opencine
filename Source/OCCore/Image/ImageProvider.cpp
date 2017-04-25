#include "ImageProvider.h"

#include <chrono>
#include <string>

#include "Log/Logger.h"

#include "TIFFLoader.h"
#include "MLVLoader.h"

using namespace OC::DataProvider;

ImageProvider::ImageProvider()
{
    _imageProviders.insert(std::make_pair(FileFormat::TIFF, std::make_shared<TIFFLoader>()));
    _imageProviders.insert(std::make_pair(FileFormat::MLV, std::make_shared<MLVLoader>()));

    //_imageProviders[FileFormat::TIFF] = std::make_shared<TIFFLoader>();
    //_imageProviders[FileFormat::MLV] = std::make_shared<MLVLoader>();
}

bool ImageProvider::ReadBinaryFile(std::string fileName, int& length, uint8_t*& fileData) const
{
    std::ifstream is;
    is.open(fileName, std::ios::binary);

    if (!is.is_open())
    {
        std::cout << "ImageProvider: File couldn't be opened" << std::endl;
        return false;
    }

    // get length of file:
    is.seekg(0, std::ios::end);
    length = is.tellg();
    is.seekg(0, std::ios::beg);

    // allocate memory:
    fileData = new uint8_t[length];

    // read data as a block:
    is.read(reinterpret_cast<char*>(fileData), length);
    is.close();
    return true;
}

void ImageProvider::Load(std::string fileName, FileFormat format, OCImage& image, IAllocator& allocator) const
{
    int length = -1;
    uint8_t* fileData = nullptr;

    auto start = std::chrono::high_resolution_clock::now();

    if (!ReadBinaryFile(fileName, length, fileData))
    {
        OC_LOG_ERROR("Failed to load file: " + fileName);
        return;
    }

    auto diffTime = std::chrono::high_resolution_clock::now() - start;
    auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

    auto log = "File loading: " + std::to_string(frameTime) + "ms";
    OC_LOG_INFO(log);

    start = std::chrono::high_resolution_clock::now();
    IImageLoader* imageLoader = nullptr;
    // TODO: Rework this hacky implementation


    //    if (_imageProviders.find(format) != _imageProviders.end())
    //    {
    //        imageLoader = _imageProviders[format];
    //    }

    auto it = _imageProviders.find(format);
    if (it != _imageProviders.end())
    {
        imageLoader = it->second.get();
    }

    imageLoader->Load(fileData, length, image, allocator);

    //    if (format == FileFormat::DNG)
    //    {
    //        //imageLoader = new TIFFLoader();
    //        imageLoader->Load(fileData, length, image, allocator);
    //    }
    //    else if(format == FileFormat::MLV)
    //    {
    //        //imageLoader = new MLVLoader();
    //        imageLoader->Load(fileData, length, image, allocator);
    //    }

    diffTime = std::chrono::high_resolution_clock::now() - start;
    frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

    log = "File processing: " + std::to_string(frameTime) + "ms";
    OC_LOG_INFO(log);

    //delete imageLoader;

    delete[] fileData;
}
