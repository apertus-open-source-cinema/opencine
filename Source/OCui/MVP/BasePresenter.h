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
            Q_OBJECT

            // TODO: Evaluate use of some general interface, as C++ isn't allowing virtual templates, PIMPL should be considered.
            OCEventBus _eventBus;

        protected:
            OCEventBus& GetEventBus()
            {
                return _eventBus;
            }

        public:
            BasePresenter(OCEventBus& bus)
            {
            }
        };
    }
}
#endif //BASEPRESENTER_H
