// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef PROCESSINGPRESENTER_H
#define PROCESSINGPRESENTER_H

#include <memory>

#include "Interfaces/IProcessingPresenter.h"
#include "Interfaces/IProcessingView.h"

#include <Image/ImageProvider.h>
#include <Image/IDebayerProcessor.h>

using namespace OC::DataProvider;

class ProcessingPresenter : public IProcessingPresenter
{
    Q_OBJECT

    IProcessingView* _view;

    std::shared_ptr<OCImage> _image = std::make_shared<OCImage>();
    std::unique_ptr<ImageProvider> provider;

    std::vector<std::shared_ptr<IDebayerProcessor>> _debayerProcessors;
    int _currentDebayerProcessor;

    std::string _currentFilePath;

public:
    explicit ProcessingPresenter(IProcessingView& view);

    void Test();

    void Show();

protected slots:
    void OpenRAWFile();
    void ChangeDebayerMethod(int debayerMethod);
};

#endif // PROCESSINGPRESENTER_H
