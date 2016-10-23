#ifndef ITASK_H
#define ITASK_h

#include "OCCore_export.h"

class OCCORE_EXPORT ITask
{
public:
	virtual ~ITask() {}

	virtual void Run() = 0;
};

#endif //ITASK_H
