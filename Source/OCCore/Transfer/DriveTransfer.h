#ifndef DRIVETRANSFER_H
#define DRIVETRANSFER_H

#include "../API/IDataTransfer.h"

#include "OCCore_export.h"

class OCCORE_EXPORT DriveTransfer : public IDataTransfer
{
	void ReplicateFolderStructure(std::string rootPath, std::string targetPath) const;

public:
	DriveTransfer();
	
	void StartTransfer() override;
};

#endif // DRIVETRANSFER_H
