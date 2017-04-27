#ifndef HASHCHECKTASK_H
#define HASHCHECKTASK_H

#include <memory>

#include "ITask.h"
#include "Hash/xxHashAdapter.h"

#include "OCCore_export.h"

class OCCORE_EXPORT HashCheckTask : public ITask
{
	Q_OBJECT

	std::unique_ptr<IHashGenerator> _hashGenerator = nullptr;

	std::string _fileName;
    uint64_t _checkSum;

	int GetFileSize(std::ifstream& fin) const;
	
public:
    HashCheckTask(std::string fileName, uint64_t checkSum);
	virtual ~HashCheckTask();

	int GetProgressPercentage() override { return 0; }
	std::string GetTaskDescription() override { return "Checksum verification"; }
	std::string GetSubTaskDescription() override { return "CO_test_???.mov"; }

public slots:
	void Execute();

signals:
    void HashChecked(uint64_t checksum);
};

#endif //HASHCHECKTASK_H
