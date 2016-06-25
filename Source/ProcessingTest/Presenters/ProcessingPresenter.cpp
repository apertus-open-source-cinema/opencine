#include "ProcessingPresenter.h"

#include <chrono>

#include <QThread>

#include <Image/BilinearDebayer.h>
#include <Image/NearestNeighborScaler.h>
#include <Log/Logger.h>
#include <Memory/StaticAllocator.h>
#include "Image/SHOODAKDebayer.h"

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view)
{
	_view = &view;

	provider.reset(new ImageProvider());
}

void ProcessingPresenter::Test()
{
	auto start = std::chrono::high_resolution_clock::now();

	//provider->Load("helloworld-ML-cleanup.DNG", FileFormat::DNG, *_image.get());

	//OC_LOG_INFO(frameTimeLog);
	//OC::Log::Logger::GetInstance().LogInfo("TEST1234");

	IAllocator* poolAllocator = new RawPoolAllocator(50 * 1024 * 1024);

	OC_LOG_INFO("Loading image");
    provider->Load("darklab-frame00004.dng", FileFormat::DNG, *_image.get(), *poolAllocator);
    //provider->Load("greenscreen-frame00003.dng", FileFormat::DNG, *_image.get(), *poolAllocator);
	//provider->Load("Shot 1/Frame000320.dng", FileFormat::DNG, *_image.get(), *poolAllocator);
	OC_LOG_INFO("Loading finished");

	OC_LOG_INFO("Demosaicing");
    //BilinearDebayer* debayer = new BilinearDebayer(*_image.get());
    SHOODAKDebayer* debayer = new SHOODAKDebayer(*_image.get());
	debayer->Process();
	OC_LOG_INFO("Demosaicing finished");

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
	OC_LOG_INFO("Conversion finished");

	_view->SetThumbnail(_image->Width(), _image->Height(), interleavedArray);

	//delete[] interleavedArray;
}
