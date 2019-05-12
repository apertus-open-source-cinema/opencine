// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "ProcessingPresenter.h"

#include <chrono>
#include <vector>

#include <QFileDialog>
#include <QFileInfo>
#include <QStringList>
#include <QThread>

#include <Image/BilinearDebayer.h>
#include <Image/BilinearDebayerOMP.h>

#include <Image/GEDIDebayer.h>
#include <Image/GEDIDebayerOMP.h>

#include "Image/SHOODAKDebayer.h"
#include "Image/SHOODAKDebayerOMP.h"

#include <Image/NearestNeighborScaler.h>

#include "Image/EndianHelper.h"
#include "Image/RawDump.h"
#include <Log/Logger.h>
#include <Memory/StaticAllocator.h>

using namespace OC::DataProvider;
using namespace OC::Image;

ProcessingPresenter::ProcessingPresenter(IProcessingView& view) : _currentDebayerProcessor(0), _lastDir(QDir::currentPath())
{
    _view = &view;

    QStringList debayerMethods = {"Bilinear", "GEDI", "SHOODAK", "Bilinear (OMP)", "GEDI (OMP)", "SHOODAK (OMP)", "None"};
    _view->SetAvailableDebayerMethods(debayerMethods);

    _debayerProcessors.push_back(std::make_shared<BilinearDebayer>());
    _debayerProcessors.push_back(std::make_shared<GEDIDebayer>());
    _debayerProcessors.push_back(std::make_shared<SHOODAKDebayer>());
    _debayerProcessors.push_back(std::make_shared<BilinearDebayerOMP>());
    _debayerProcessors.push_back(std::make_shared<GEDIDebayerOMP>());
    _debayerProcessors.push_back(std::make_shared<SHOODAKDebayerOMP>());

    provider.reset(new ImageProvider());

    connect(_view, &IProcessingView::OpenRAWFile, this, &ProcessingPresenter::OpenRAWFile);
    connect(_view, SIGNAL(DebayerMethodChanged(int)), this, SLOT(ChangeDebayerMethod(int)));
    connect(_view, SIGNAL(DumpPNG()), this, SLOT(DumpPNG()));
}

void ProcessingPresenter::Show()
{
    auto start = std::chrono::high_resolution_clock::now();

    IAllocator* poolAllocator = new RawPoolAllocator(150 * 1024 * 1024);

    OC_LOG_INFO("Loading image");
    // File format is set to "unknown" to let OC determine it automatically
    provider->Load(_currentFilePath, FileFormat::Unknown, *_image.get(), *poolAllocator);

    OC_LOG_INFO("Loading finished");

    OC_LOG_INFO("Demosaicing");
    if(_currentDebayerProcessor != 6)
    {
        _debayerProcessors[_currentDebayerProcessor]->Process(*_image.get());
    }
    OC_LOG_INFO("Demosaicing finished");

    auto diffTime = std::chrono::high_resolution_clock::now() - start;
    auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();

    std::string frameTimeLog = "Frame loading time: " + std::to_string(frameTime) + "ms";
    OC_LOG_INFO(frameTimeLog);

    _view->SetFrame(*_image.get());
}

// TODO: Check how to remove allFormats, as it is used as workaround for filter selection in QFileDialog
void ProcessingPresenter::CreateFileFilters(std::unordered_map<std::string, std::string> filterList,
                                            std::string& concatenatedFormats, std::string& allFormats)
{
    allFormats = "All suppported formats(";
    for(auto& format : filterList)
    {
        allFormats += ' ' + format.second;
    }
    allFormats += ')';

    for(auto& format : filterList)
    {
        concatenatedFormats += format.first + '(' + format.second + ");;";
    }
    concatenatedFormats += allFormats;
}

void ProcessingPresenter::OpenRAWFile()
{
    _view->EnableRendering(false);

    std::unordered_map<std::string, std::string> supportedFormatsList = {{"DNG Files", "*.dng *.DNG"},
                                                                         {"MagicLantern files", "*.mlv *.MLV"}};

    std::string formats, allFormats;
    CreateFileFilters(supportedFormatsList, formats, allFormats);

    QString fileName =
        QFileDialog::getOpenFileName(_view, tr("Open Image"), _lastDir, formats.c_str(), new QString(allFormats.c_str()));

    _currentFilePath = fileName.toStdString();
    _lastDir = QFileInfo(fileName).path();

    Show();

    _view->EnableRendering(true);
}

void ProcessingPresenter::ChangeDebayerMethod(unsigned int debayerMethod)
{
    _currentDebayerProcessor = debayerMethod;
    Show();
}

void ProcessingPresenter::DumpPNG()
{
    _view->EnableRendering(false);
    QString fileName = QFileDialog::getSaveFileName(_view, tr("Save PNG"), QDir::currentPath(), tr("PNG Files(*.png *.PNG)"));

    OC::Image::RawDump::DumpPNG(fileName.toStdString(), *_image.get());

    _view->EnableRendering(true);
}
