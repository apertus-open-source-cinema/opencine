#ifndef ITASKPROGRESS_H
#define ITASKPROGRESS_H

#include <string>
#include <QObject>

// Used for progress and status reporting, which will be used in ProgressDialog (see OCui)
class ITaskProgress : public QObject
{
    Q_OBJECT

protected:
    unsigned int _progressPercentage;

public:
	virtual ~ITaskProgress()
	{
	}

	// TODO: Evaluate if float value is required
    virtual unsigned int GetProgressPercentage() = 0;

	virtual std::string GetTaskDescription() = 0;
	virtual std::string GetSubTaskDescription() = 0;

signals:
    void TaskUpdated();
};

#endif //ITASKPROGRESS_H
