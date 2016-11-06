#ifndef DRIVETRANSFER_H
#define DRIVETRANSFER_H

#include <vector>

#include "API/IDataTransfer.h"
#include "OCCore_export.h"

class OCCORE_EXPORT DriveTransfer : public IDataTransfer
{
	std::string _sourcePath;
	std::vector<std::string> _destinationPaths;

	void ReplicateFolderStructure(std::string rootPath, std::string targetPath) const;

public:
	// TODO: Add setters for source and destination paths to be able to reuse DriveTransfer
	DriveTransfer(std::string sourcePath, std::vector<std::string> destinationPaths);
	
	void StartTransfer() override;
};

#endif // DRIVETRANSFER_H
