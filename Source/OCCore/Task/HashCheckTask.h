#ifndef HASHCHECKTASK_H
#define HASHCHECKTASK_H

#include <memory>

#include "ITask.h"
#include "Transfer/FileTransferInfo.h"
#include "Hash/xxHashAdapter.h"

#include "OCCore_export.h"

class OCCORE_EXPORT HashCheckTask : public ITask
{
	Q_OBJECT

	std::unique_ptr<IHashGenerator> _hashGenerator = nullptr;

    std::vector<FileTransferInfo>* _fileList;
    unsigned int _currentFileIndex;

    long GetFileSize(std::ifstream& fin) const;

    void UpdateProgress(unsigned int index, unsigned int progress, unsigned int progressBlock);

public:
    HashCheckTask(std::vector<FileTransferInfo>* fileList);
	virtual ~HashCheckTask();

    unsigned int GetProgressPercentage() override;
    std::string GetTaskDescription() override;
    std::string GetSubTaskDescription() override;

public slots:
	void Execute();

private slots:
    void ProgressChanged(unsigned int progress);

signals:
    void HashChecked(uint64_t checksum);
};

#endif //HASHCHECKTASK_H
