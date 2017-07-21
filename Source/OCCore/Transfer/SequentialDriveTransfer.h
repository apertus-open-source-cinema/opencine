// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef SEQUENTIALDRIVETRANSFER_H
#define SEQUENTIALDRIVETRANSFER_H

#include <vector>

#include "API/IDataTransfer.h"
#include "FileTransferInfo.h"

#include "OCCore_export.h"

class OCCORE_EXPORT SequentialDriveTransfer : public ITask
{
	Q_OBJECT

	std::string _sourcePath;
	std::vector<std::string> _destinationPaths;
    std::vector<FileTransferInfo>* _fileList;

    std::string _subTaskDescription;

    void ReplicateFolderStructure(std::string& rootPath, std::string& targetPath) const;

public:
    // TODO: Add setters for source and destination paths to be able to reuse SequentialDriveTransfer
    SequentialDriveTransfer(std::string sourcePath, std::vector<std::string> destinationPaths, std::vector<FileTransferInfo>* fileList);

    unsigned int GetProgressPercentage() override;
	std::string GetTaskDescription() override;
	std::string GetSubTaskDescription() override;
    void TransferFile(QString sourcePath, QString relativeFilePath, QString targetPath, int64_t& checksum);

public slots:
	void Execute();

private slots:
    void ProgressChanged(unsigned int progress);

signals:
	void CopyProgressChanged(int progress);
	void FileTransfered(int index, int64_t checksum);
	void TransferFinished();
	// TODO: Add signal to notify about finished copying of a file, e.g. to start hash verification process
};

#endif //SEQUENTIALDRIVETRANSFER_H
