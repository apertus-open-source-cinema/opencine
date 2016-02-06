#include "ProcessingPresenter.h"

#include <Image/ImageProvider.h>
#include <Image/NearestNeighborScaler.h>

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view)
{
    _view = &view;

    std::unique_ptr<ImageProvider> provider(new ImageProvider());

    //provider->Load("000100.dng", FileFormat::DNG, *_image);

    provider->Load("Frame000338.dng", FileFormat::DNG, *_image);
    std::unique_ptr<NearestNeighborScaler> scaler(new NearestNeighborScaler(*_image));
    //std::unique_ptr<IFrameProcessor> frameProcessor(new BayerFrameProcessor());

    //frameProcessor->SetData(*image->Data(), image->Width(), image->Height(), SourceFormat::Integer12);
    //frameProcessor->Process();

    _view->SetFrame(*_image.get());
}
