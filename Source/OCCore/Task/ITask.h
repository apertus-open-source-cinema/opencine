#ifndef ITASK_H
#define ITASK_H

#include "OCCore_export.h"
#include "ITaskProgress.h"

class OCCORE_EXPORT ITask : public ITaskProgress
{
    Q_OBJECT


protected:
    unsigned int _id;

public:
    ITask()
    {
        GenerateTaskID();
    }

    ~ITask()
    {
    }

    unsigned int GetID()
    {
        return _id;
    }

private:
    void GenerateTaskID()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned int> dist(100001, 999999);
        _id = dist(mt);
    }

signals:
    // TODO: Needs evaluation, switched to pointer as there are some problems with passing by reference and Qt type registration for abstract classes
    void TaskUpdated(ITask*);
};


#endif //ITASK_H
