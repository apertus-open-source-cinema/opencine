#ifndef FILETRANSFERINFO_H
#define FILETRANSFERINFO_H

// TODO: Consider further states, like "Aborted" to be able to resume transfer, e.g. after user intervention
enum class TransferState
{
	NotStarted,
	Failed,
	Successful
};

// TODO: Check if class is better suited
struct FileTransferInfo
{
	std::string FileName = "";
	std::string RelativeFolderPath = ""; // Relative path
    std::string FullTargetPath = "";
	uint64_t Checksum = 0;
	bool Transfered = false;
	TransferState State = TransferState::NotStarted;
};

#endif //FILETRANSFERINFO_H
