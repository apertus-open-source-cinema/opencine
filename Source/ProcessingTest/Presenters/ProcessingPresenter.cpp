#include "ProcessingPresenter.h"

using namespace OC::DataProvider;

ProcessingPresenter::ProcessingPresenter(IProcessingView &view)
{
    std::unique_ptr<Image> image;

    std::unique_ptr<ImageProvider> provider(new ImageProvider());
}
