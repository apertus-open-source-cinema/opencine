#ifndef ITASK_H
#define ITASK_H

#include "OCCore_export.h"
#include "ITaskProgress.h"

class OCCORE_EXPORT ITask : public ITaskProgress
{
	Q_OBJECT

public:
	virtual ~ITask()
	{
	}

	virtual void Execute() = 0;
};

#endif //ITASK_H
