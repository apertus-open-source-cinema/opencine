#ifndef PROCESSINGPRESENTER_H
#define PROCESSINGPRESENTER_H

#include <memory>

#include "Interfaces/IProcessingPresenter.h"
#include "Interfaces/IProcessingView.h"

class ProcessingPresenter : public IProcessingPresenter
{
    IProcessingView* _view;

    std::shared_ptr<OCImage> _image = std::make_shared<OCImage>();

public:
    explicit ProcessingPresenter(IProcessingView& view);
};

#endif // PROCESSINGPRESENTER_H
