// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "ProcessingPresenter.h"

#include <chrono>

#include <QThread>

#include <Image/BilinearDebayer.h>
#include <Image/NearestNeighborScaler.h>
#include <Log/Logger.h>
#include <Memory/StaticAllocator.h>

#include "Image/SHOODAKDebayer.h"

#include "Image/EndianHelper.h"
#include "Image/RawDump.h"

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view)
{
    _view = &view;

    provider.reset(new ImageProvider());
}

void ProcessingPresenter::Test()
{
    auto start = std::chrono::high_resolution_clock::now();

    IAllocator* poolAllocator = new RawPoolAllocator(50 * 1024 * 1024);

    OC_LOG_INFO("Loading image");
    provider->Load("test_frame.dng", FileFormat::DNG, *_image.get(), *poolAllocator);
//    provider->Load("M11-1526.VB.mlv", FileFormat::MLV, *_image.get(), *poolAllocator);
    OC_LOG_INFO("Loading finished");

    OC_LOG_INFO("Demosaicing");
    BilinearDebayer* debayer = new BilinearDebayer(*_image.get());
    //SHOODAKDebayer* debayer = new SHOODAKDebayer(*_image.get());
    //debayer->Process();
    //OC_LOG_INFO("Demosaicing finished");

    auto diffTime = std::chrono::high_resolution_clock::now() - start;
    auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

    std::string frameTimeLog = "Frame loading time: " + std::to_string(frameTime) + "ms";
    OC_LOG_INFO(frameTimeLog);

    _view->SetFrame(*_image.get());

    OC_LOG_INFO("Convert to interleaved array");
    unsigned int dataLength = _image->Width() * _image->Height();
    unsigned char* interleavedArray = new unsigned char[dataLength * 3];
    unsigned int i = 0;

    unsigned short*  redArray = static_cast<unsigned short*>(_image->RedChannel());
    unsigned short*  greenArray = static_cast<unsigned short*>(_image->GreenChannel());
    unsigned short*  blueArray = static_cast<unsigned short*>(_image->BlueChannel());

    //#pragma omp for private(interleavedArray, i)
    for (; i < dataLength; i++)
    {
        interleavedArray[i * 3] = (redArray[i] >> 4) * 1.0;
        interleavedArray[i * 3 + 1] = (greenArray[i] >> 4)  * 1.0;
        interleavedArray[i * 3 + 2] = (blueArray[i] >> 4) * 1.0;
    }
    unsigned char dummydata[] = "This is a dummy data to just test if the dump feature works or not.";
    OC::Image::RawDump::Dump("DummyDump.dat", dummydata, strlen((const char*)dummydata));
    OC::Image::RawDump::Dump("InterleavedArray.dat", interleavedArray, dataLength * 3);
    OC_LOG_INFO("Conversion finished");

    _view->SetThumbnail(_image->Width(), _image->Height(), interleavedArray);

    //delete[] interleavedArray;
}
