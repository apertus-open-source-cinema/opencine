#include <Catch2/catch.hpp>

#include <chrono>

#include "../OCcore/Image/BaseOCL.h"
#include "../OCcore/Image/BilinearProcessorOCL.h"
#include "../OCcore/Image/ImageProvider.h"
#include "../OCcore/Log/Logger.h"
#include "../OCcore/Memory/StaticAllocator.h"

#define NUM_TRIES 50

TEST_CASE("Bilinear OCL Benchmark", "[OC::Image]")
{
    IAllocator* poolAllocator = new RawPoolAllocator(50 * 1024 * 1024);

    std::unique_ptr<OC::Image::OCImage> image(new OC::Image::OCImage());

    OC_LOG_INFO("Loading image.");
    std::unique_ptr<OC::DataProvider::ImageProvider> provider(new OC::DataProvider::ImageProvider());
    provider->Load("bench_frame.dng", OC::Image::FileFormat::DNG, *image.get(), *poolAllocator);
    OC_LOG_INFO("Load finished.");

    OC_LOG_INFO("Benchmarking...");

    BaseOCL* ocl = new BaseOCL();
    ocl->SetupOCL();

    cl::Context context = ocl->GetContext();

    BilinearProcessorOCL bilinearProcessor;

    ocl->RegisterProcessor(&bilinearProcessor, *image);

    auto demosaicTime = 0;

    for(int i = 0; i < NUM_TRIES; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        ocl->ExecuteProcessor();
        uint16_t* imageRed = (uint16_t*)bilinearProcessor.GetRedChannel();
        uint16_t* imageGreen = (uint16_t*)bilinearProcessor.GetGreenChannel();
        uint16_t* imageBlue = (uint16_t*)bilinearProcessor.GetBlueChannel();

        auto diffTime = std::chrono::high_resolution_clock::now() - start;
        demosaicTime += std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();
    }

    OC_LOG_INFO("\nBenchmark finished:\nALGORITHM> BilinearOCL\nNUM_TRIES> " + std::to_string(NUM_TRIES) + "\nAVG TIME > " +
                std::to_string(demosaicTime / NUM_TRIES) + "ms\n");
}
