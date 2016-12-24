#ifndef PROGRESSDIALOGPRESENTER_H
#define PROGRESSDIALOGPRESENTER_H

#include "Controls/ProgressDialog.h"
#include "Events/EventBus.h"

#include "OCui_export.h"

class OCUI_EXPORT ProgressDialogPresenter : public QObject
{
	Q_OBJECT

	ProgressDialog* _view;
	OCEventBus* _eventBus;

	std::vector<ITask*> _taskList;

public:
	ProgressDialogPresenter(ProgressDialog& view, OCEventBus* eventBus);

	void NewTaskHandler(const OCEvent& event);

protected:
	OCEventBus* GetEventBus() const
	{
		return _eventBus;
	}

private slots:
	void ProgressChanged(int progress) const;
};

#endif //PROGRESSDIALOGPRESENTER_H
