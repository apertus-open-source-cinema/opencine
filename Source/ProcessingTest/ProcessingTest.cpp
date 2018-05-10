// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include <memory>
#include <thread>

#include <OCui.h>

#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>

#include "Views/ProcessingView.h"
#include "Presenters/ProcessingPresenter.h"

#include <Image/FramePool.h>
#include "Log/Logger.h"

class ProcessingTest : public OCui::GUIApplication
{
	std::shared_ptr<IProcessingView> _view;
	std::shared_ptr<IProcessingPresenter> _presenter;

public:
	ProcessingTest(int& argc, char** argv) : OCui::GUIApplication(argc, argv, "ProcessingTest")
	{
        _view = std::make_shared<ProcessingView>();
		_presenter = std::make_shared<ProcessingPresenter>(*_view);

		SetLayout(*static_cast<QWidget*>(_view.get()));
		ShowMaximized();

        _presenter->Test();
	}
};

int main(int argc, char** argv)
{
	OC_LOG_INFO("-----");
	OC_LOG_INFO("ProcessingTest started");

	ProcessingTest* app = new ProcessingTest(argc, argv);
	app->Run();

	if (app != nullptr)
	{
		delete app;
	}

	OC_LOG_INFO("ProcessingTest exited");
	OC_LOG_INFO("-----");
	return 0;
}
