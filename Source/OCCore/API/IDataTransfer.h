#ifndef IDATATRANSFER_H
#define IDATATRANSFER_H

#include <string>
#include "Task/ITask.h"

class IDataTransfer : public ITask
{
public:
	virtual ~IDataTransfer()
	{
	}

    IDataTransfer(std::string sourcePath = "", std::string targetPath = "")
	{
	}
};

#endif // IDATATRANSFER_H
