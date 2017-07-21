// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

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
