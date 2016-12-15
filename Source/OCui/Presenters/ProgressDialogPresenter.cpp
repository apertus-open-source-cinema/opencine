#include "ProgressDialogPresenter.h"

ProgressDialogPresenter::ProgressDialogPresenter(ProgressDialog& view, OCEventBus* eventBus):
	_view(&view),
	_eventBus(eventBus)
{
	_eventBus->RegisterEventHandler<RegisterNewTaskEvent, ProgressDialogPresenter>(std::bind(&ProgressDialogPresenter::NewTaskHandler, this, std::placeholders::_1));
}

void ProgressDialogPresenter::NewTaskHandler(const OCEvent& event)
{
	// TODO: Conversion is necessary at the moment, as arguments are not polymorphic yet
	const RegisterNewTaskEvent taskEvent = dynamic_cast<const RegisterNewTaskEvent&>(event);
	// 1. Add event to a list
	ITask* task = taskEvent.GetTask();
	_taskList.push_back(task);

	connect(task, SIGNAL(CopyProgressChanged(int)), this, SLOT(ProgressChanged(int)));
	// 2. Connect to progress events of task directly, event bus not needed here as it's rather specific (at least for now)
	//std::bind / std::function
	_view->AddTask(task);
	

	_view->show();
}

void ProgressDialogPresenter::ProgressChanged(int progress)
{
	QString progressString = QString("Progress: %1%").arg(progress);
	qDebug(progressString.toLatin1());
	_view->SetTaskProgress(0, progress);
}
