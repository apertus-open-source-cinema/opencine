#ifndef ITASK_H
#define ITASK_h

#include "OCCore_export.h"

class OCCORE_EXPORT ITask
{
	virtual void Run() = 0;
};

#endif //ITAASK_H