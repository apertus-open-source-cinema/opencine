#ifndef PROGRESSDIALOGPRESENTER_H
#define PROGRESSDIALOGPRESENTER_H

#include "Controls/ProgressDialog.h"
#include "Events/EventBus.h"

class ProgressDialogPresenter
{
	ProgressDialog* _view;
	OCEventBus* _eventBus;

public:
	ProgressDialogPresenter(ProgressDialog& view, OCEventBus* eventBus) :
		_view(&view),
		_eventBus(eventBus)
	{
	}

protected:
	OCEventBus* GetEventBus() const
	{
		return _eventBus;
	}
};

#endif //PROGRESSDIALOGPRESENTER_H
