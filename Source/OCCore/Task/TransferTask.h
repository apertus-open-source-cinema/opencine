#ifndef TRANSFERTASK_H
#define TRANSFERTASK_H

#include "ITask.h"

#include "OCCore_export.h"

class OCCORE_EXPORT TransferTask : public ITask
{
public:
	TransferTask();

	virtual void Run() override
	{

	}
};

#endif //TRANSFERTASK_H