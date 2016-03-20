#include "ProcessingPresenter.h"

#include <chrono>

#include <QThread>

#include <Image/BilinearDebayer.h>
#include <Image/NearestNeighborScaler.h>
#include <Log/Logger.h>

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view)
{
    _view = &view;

    provider.reset(new ImageProvider());
}

void ProcessingPresenter::Test()
{
        auto start = std::chrono::high_resolution_clock::now();
        provider->Load("Shot 1/Frame000320.dng", FileFormat::DNG, *_image.get());
        //provider->Load("helloworld-ML-cleanup.DNG", FileFormat::DNG, *_image.get());

        auto diffTime = std::chrono::high_resolution_clock::now() - start;
        auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

        std::string frameTimeLog = "Frame loading time: " + std::to_string(frameTime) + "ms";
        //OC_LOG_INFO(frameTimeLog);
        //OC::Log::Logger::GetInstance().LogInfo("TEST1234");
        OC_LOG_INFO("TEST4321");

        BilinearDebayer* debayer = new BilinearDebayer(*_image.get());
        debayer->Process();

        _view->SetFrame(*_image.get());
}
