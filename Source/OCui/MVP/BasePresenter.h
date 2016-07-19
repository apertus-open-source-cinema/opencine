#ifndef BASEPRESENTER_H
#define BASEPRESENTER_H

#include "IView.h"

namespace OC
{
    namespace UI
    {
        class BasePresenter : public QObject
        {
            Q_OBJECT

        public:
            BasePresenter()
            {
            }
        };
    }
}
#endif //BASEPRESENTER_H
