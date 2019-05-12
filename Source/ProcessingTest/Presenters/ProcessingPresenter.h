// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef PROCESSINGPRESENTER_H
#define PROCESSINGPRESENTER_H

#include <memory>

#include "Interfaces/IProcessingPresenter.h"
#include "Interfaces/IProcessingView.h"

#include <Image/IDebayerProcessor.h>
#include <Image/ImageProvider.h>

class ProcessingPresenter : public IProcessingPresenter
{
    Q_OBJECT

    IProcessingView* _view;

    std::shared_ptr<OC::Image::OCImage> _image = std::make_shared<OC::Image::OCImage>();
    std::unique_ptr<OC::DataProvider::ImageProvider> provider;

    std::vector<std::shared_ptr<IDebayerProcessor>> _debayerProcessors;
    unsigned int _currentDebayerProcessor;

    std::string _currentFilePath;
    QString _lastDir;

public:
    explicit ProcessingPresenter(IProcessingView& view);

    void Show();

    void CreateFileFilters(std::unordered_map<std::string, std::string> filterList, std::string& concatenatedFormats,
                           std::string& allFormats);

protected slots:
    void OpenRAWFile();
    void ChangeDebayerMethod(unsigned int debayerMethod);
    void DumpPNG();
};

#endif // PROCESSINGPRESENTER_H
