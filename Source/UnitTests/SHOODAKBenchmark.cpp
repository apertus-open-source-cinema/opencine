#include <Catch2/catch.hpp>

#include <chrono>

#include "../OCcore/Image/ImageProvider.h"
#include "../OCcore/Image/SHOODAKDebayer.h"
#include "../OCcore/Log/Logger.h"
#include "../OCcore/Memory/StaticAllocator.h"

#define NUM_TRIES 50

TEST_CASE("SHOODAK Benchmark", "[OC::Image]")
{
    IAllocator* poolAllocator = new RawPoolAllocator(50 * 1024 * 1024);

    std::unique_ptr<OC::Image::OCImage> image(new OC::Image::OCImage());

    OC_LOG_INFO("Loading image.");
    std::unique_ptr<OC::DataProvider::ImageProvider> provider(new OC::DataProvider::ImageProvider());
    provider->Load("bench_frame.dng", OC::Image::FileFormat::DNG, *image.get(), *poolAllocator);
    OC_LOG_INFO("Load finished.");

    OC_LOG_INFO("Benchmarking...");

    std::unique_ptr<SHOODAKDebayer> debayer(new SHOODAKDebayer(*image));
    auto demosaicTime = 0;

    for(int i = 0; i < NUM_TRIES; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        debayer.get()->Process();

        auto diffTime = std::chrono::high_resolution_clock::now() - start;
        demosaicTime += std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();
    }

    OC_LOG_INFO("\nBenchmark finished:\nALGORITHM> SHOODAK\nNUM_TRIES> " + std::to_string(NUM_TRIES) + "\nAVG TIME > " +
                std::to_string(demosaicTime / NUM_TRIES) + "ms\n");
}
