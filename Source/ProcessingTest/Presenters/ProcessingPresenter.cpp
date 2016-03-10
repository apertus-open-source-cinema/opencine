#include "ProcessingPresenter.h"

#include <chrono>

#include <QThread>

#include <Image/BilinearDebayer.h>
#include <Image/NearestNeighborScaler.h>

#include <Log/ILogger.h>

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view)
{
    _view = &view;

    provider.reset(new ImageProvider());
}

//LOG_WARNING("Test 4321");
/*LogError("Test");
LogFatal("Test");
LogInfo("Test")*/;

void ProcessingPresenter::Test()
{
    //provider->Load("000100.dng", FileFormat::DNG, *_image);

    //provider->Load("Shot 1/Frame000320.dng", FileFormat::DNG, *_image);

    //provider->Load("Frame000338.dng", FileFormat::DNG, *_image);
    //std::unique_ptr<NearestNeighborScaler> scaler(new NearestNeighborScaler(*_image));
    //std::unique_ptr<IFrameProcessor> frameProcessor(new BayerFrameProcessor());

    //frameProcessor->SetData(*image->Data(), image->Width(), image->Height(), SourceFormat::Integer12);
    //frameProcessor->Process();

//    while(true)
//    {
//        if(_image == nullptr)
//        {
//            return;
//        }

        //OC_LOG_WARNING("Loading file: Shot 1/Frame000320.dng");
        //OC_LOG_ERROR("Loading file: Shot 1/Frame000320.dng failed");
        auto start = std::chrono::high_resolution_clock::now();
        provider->Load("Shot 1/Frame000320.dng", FileFormat::DNG, *_image.get());

        auto diffTime = std::chrono::high_resolution_clock::now() - start;
        auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

        std::string frameTimeLog = "Frame loading time: " + std::to_string(frameTime) + "ms";
        OC_LOG_INFO(frameTimeLog);

        BilinearDebayer* debayer = new BilinearDebayer(*_image.get());
        debayer->Process();

        _view->SetFrame(*_image.get());


//        QThread::sleep(1);

//        if(_image == nullptr)
//        {
//            return;
//        }

       // LOG_WARNING("Loading file: Shot 1/Frame000338.dng");
        //provider->Load("Shot 1/Frame000338.dng", FileFormat::DNG, *_image.get());
        //_view->SetFrame(*_image.get());
        //QThread::sleep(1);

        //if(_image == nullptr)
//        {
//            return;
//        }

        //LOG_WARNING("Loading file: Shot 1/Frame000460.dng");
//        provider->Load("Shot 1/Frame000460.dng", FileFormat::DNG, *_image.get());
//        _view->SetFrame(*_image.get());
//        QThread::sleep(1);
//    }
}
