#ifndef PROCESSINGPRESENTER_H
#define PROCESSINGPRESENTER_H

#include "Interfaces/IProcessingPresenter.h"
#include "Interfaces/IProcessingView.h"

class ProcessingPresenter : public IProcessingPresenter
{
    IProcessingView* _view;

public:
    explicit ProcessingPresenter(IProcessingView& view);
};

#endif // PROCESSINGPRESENTER_H
