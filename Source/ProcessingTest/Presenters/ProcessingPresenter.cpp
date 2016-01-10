#include "ProcessingPresenter.h"

#include <memory>

#include <Image/ImageProvider.h>
#include "API/IFrameProcessor.h"

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view)
{
    _view = &view;

    std::unique_ptr<OCImage> image(new OCImage());
    std::unique_ptr<ImageProvider> provider(new ImageProvider());

    provider->Load("Frame000338.dng", FileFormat::DNG, *image);
    std::unique_ptr<IFrameProcessor> frameProcessor(new BayerFrameProcessor());

    frameProcessor->SetData(*image->Data(), image->Width(), image->Height(), SourceFormat::Integer12);
    frameProcessor->Process();

    _view->SetFrame(*image.get());
}
