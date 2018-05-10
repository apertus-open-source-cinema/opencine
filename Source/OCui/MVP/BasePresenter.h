// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef BASEPRESENTER_H
#define BASEPRESENTER_H

#include "IView.h"

#include <Events/EventBus.h>

namespace OC
{
	namespace UI
	{
		class BasePresenter : public QObject
		{
			// TODO: Evaluate use of some general interface, as C++ isn't allowing virtual templates, PIMPL should be considered.
			OCEventBus* _eventBus;

		protected:
			OCEventBus* GetEventBus()
			{
				return _eventBus;
			}

		public:
			explicit BasePresenter(OCEventBus* bus) :
			_eventBus(bus)
			{
			}
		};
	}
}
#endif //BASEPRESENTER_H
