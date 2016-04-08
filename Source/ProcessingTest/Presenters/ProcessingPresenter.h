#ifndef PROCESSINGPRESENTER_H
#define PROCESSINGPRESENTER_H

#include <memory>

#include "Interfaces/IProcessingPresenter.h"
#include "Interfaces/IProcessingView.h"

#include <Image/ImageProvider.h>

using namespace OC::DataProvider;

class ProcessingPresenter : public IProcessingPresenter
{
	IProcessingView* _view;

	std::shared_ptr<OCImage> _image = std::make_shared<OCImage>();
	std::unique_ptr<ImageProvider> provider;

public:
	explicit ProcessingPresenter(IProcessingView& view);

	void Test();
};

#endif // PROCESSINGPRESENTER_H
