#include "ProcessingPresenter.h"

#include <Image/ImageProvider.h>

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view)
{
    _view = &view;

    std::unique_ptr<ImageProvider> provider(new ImageProvider());

    provider->Load("Frame000338.dng", FileFormat::DNG, *_image);
    //std::unique_ptr<IFrameProcessor> frameProcessor(new BayerFrameProcessor());

    //frameProcessor->SetData(*image->Data(), image->Width(), image->Height(), SourceFormat::Integer12);
    //frameProcessor->Process();

    _view->SetFrame(*_image.get());
}
