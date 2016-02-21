#include "ProcessingPresenter.h"

#include <QThread>

#include <Image/NearestNeighborScaler.h>

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view)
{
    _view = &view;

    provider.reset(new ImageProvider());
}

void ProcessingPresenter::Test()
{
    //provider->Load("000100.dng", FileFormat::DNG, *_image);

    //provider->Load("Shot 1/Frame000320.dng", FileFormat::DNG, *_image);

    //provider->Load("Frame000338.dng", FileFormat::DNG, *_image);
    //std::unique_ptr<NearestNeighborScaler> scaler(new NearestNeighborScaler(*_image));
    //std::unique_ptr<IFrameProcessor> frameProcessor(new BayerFrameProcessor());

    //frameProcessor->SetData(*image->Data(), image->Width(), image->Height(), SourceFormat::Integer12);
    //frameProcessor->Process();
    while(true)
    {
        if(_image == nullptr)
        {
            return;
        }

        provider->Load("Shot 1/Frame000320.DNG", FileFormat::DNG, *_image.get());
        _view->SetFrame(*_image.get());
        QThread::sleep(1);

        if(_image == nullptr)
        {
            return;
        }

        provider->Load("Shot 1/Frame000460.dng", FileFormat::DNG, *_image.get());
        _view->SetFrame(*_image.get());
        QThread::sleep(1);
    }
}
