#ifndef DRIVETRANSFER_H
#define DRIVETRANSFER_H

#include <vector>

#include <QObject>

#include "API/IDataTransfer.h"
#include "OCCore_export.h"

class OCCORE_EXPORT DriveTransfer : public QObject, public IDataTransfer
{
	Q_OBJECT

	std::string _sourcePath;
	std::vector<std::string> _destinationPaths;

	void ReplicateFolderStructure(std::string rootPath, std::string targetPath) const;

public:
	// TODO: Add setters for source and destination paths to be able to reuse DriveTransfer
	DriveTransfer(std::string sourcePath, std::vector<std::string> destinationPaths);

	int GetProgressPercentage() override;
	std::string GetTaskDescription() override;
	std::string GetSubTaskDescription() override;

	void Execute() override;

private slots:
	void progressChanged(qint64 progress);

signals:
	void copyProgressChanged(int progress);
};

#endif // DRIVETRANSFER_H
