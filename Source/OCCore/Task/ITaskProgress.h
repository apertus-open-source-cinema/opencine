#ifndef ITASKPROGRESS_H
#define ITASKPROGRESS_H

#include <string>

// Used for progress and status reporting, which will be used in ProgressDialog (see OCui)
class ITaskProgress
{
public:
	virtual ~ITaskProgress() {}

	// TODO: Evaluate if float value is required
	virtual int GetProgressPercentage() = 0;

	virtual std::string GetTaskDescription() = 0;
	virtual std::string GetSubTaskDescription() = 0;
};

#endif //ITASKPROGRESS_H
