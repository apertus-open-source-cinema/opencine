#include <memory>
#include <thread>

#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>

#include <OCui.h>
#include <QSurfaceFormat>

#include "ProcessingTest.h"
#include "Views/ProcessingView.h"
#include "Presenters/ProcessingPresenter.h"

#include "Controls\ProgressDialog.h"

#include "Task\TransferTask.h"

class ProcessingTest : public OCui::GUIApplication
{
	std::shared_ptr<IProcessingView> _view;
	std::shared_ptr<IProcessingPresenter> _presenter;

public:
	ProcessingTest(int& argc, char** argv) : OCui::GUIApplication(argc, argv, "ProcessingTest"),
		_view(std::make_shared<ProcessingView>()),
		_presenter(std::make_shared<ProcessingPresenter>(*_view))
	{
		SetLayout(*static_cast<QWidget*>(_view.get()));
		ShowMaximized();

		ProgressDialog* progressDialog = new ProgressDialog();
		progressDialog->setModal(true);
		progressDialog->show();

		QtConcurrent::run(_presenter.get(), &IProcessingPresenter::Test);
	}
};

int main(int argc, char** argv)
{
	//std::shared_ptr<ProcessingTest> application = std::make_shared<ProcessingTest>(argc, argv);

	TransferTask* task = new TransferTask();

	delete task;

	ProcessingTest* app = new ProcessingTest(argc, argv);
	app->Run();

	if (app != nullptr)
	{
		delete app;
	}

	return 0;
}