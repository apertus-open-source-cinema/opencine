#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include "ITask.h"
#include <vector>

class TaskManager
{
	std::vector<ITask> taskList;

public:
	void ProcessTasks()
	{
		for (ITask& task : taskList)
		{
			task.Run();
		}
	}
};

#endif //TASKMANAGER_H
