// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "ImageProvider.h"

#include <chrono>
#include <string>

#include "Log/Logger.h"

#include "MLVLoader.h"
#include "TIFFLoader.h"

using namespace OC::DataProvider;
using namespace OC::Image;

IImageLoader* ImageProvider::FindSuitableLoader(uint8_t* data, std::streamsize size) const
{
    for(std::pair<OC::Image::FileFormat, std::shared_ptr<IImageLoader>> entry : _imageLoaders)
    {
        IImageLoader* imageLoader = entry.second.get();
        if(imageLoader->CheckFormat(data, size))
        {
            return imageLoader;
        }
    }

    return nullptr;
}

ImageProvider::ImageProvider()
{
    std::shared_ptr<TIFFLoader> tiffLoader = std::make_shared<TIFFLoader>();
    _imageLoaders.insert(std::make_pair(FileFormat::TIFF, tiffLoader));
    _imageLoaders.insert(std::make_pair(FileFormat::DNG, tiffLoader));
    _imageLoaders.insert(std::make_pair(FileFormat::MLV, std::make_shared<MLVLoader>()));
}

bool ImageProvider::ReadBinaryFile(std::string fileName, std::streamsize& length, uint8_t*& fileData) const
{
    std::ifstream is;
    is.open(fileName, std::ios::binary);

    if(!is.is_open())
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
    std::streamsize length = 0;
    uint8_t* fileData = nullptr;

    auto start = std::chrono::high_resolution_clock::now();

    if(!ReadBinaryFile(fileName, length, fileData))
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

    // TODO: Add error handling to prevent crash when no suitable loader was found
    if(format == FileFormat::Unknown)
    {
        imageLoader = FindSuitableLoader(fileData, length);
    }
    else
    {
        auto it = _imageLoaders.find(format);
        if(it != _imageLoaders.end())
        {
            imageLoader = it->second.get();
        }
    }

    imageLoader->Load(fileData, length, image, allocator);

    diffTime = std::chrono::high_resolution_clock::now() - start;
    frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

    log = "File processing: " + std::to_string(frameTime) + "ms";
    OC_LOG_INFO(log);

    delete[] fileData;
}
