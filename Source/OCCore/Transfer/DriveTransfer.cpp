#include "DriveTransfer.h"
#include <QDirIterator>
#include "Log/Logger.h"
#include <QStorageInfo>

void DriveTransfer::ReplicateFolderStructure(std::string rootPath, std::string targetPath) const
{
	QDir().mkdir(QString::fromStdString(targetPath));

	QDirIterator directories(QString::fromStdString(rootPath), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

	while (directories.hasNext())
	{
		directories.next();

		QString relativePath = directories.filePath();
		relativePath = relativePath.mid(static_cast<int>(rootPath.length()));
		QDir().mkdir(QString::fromStdString(targetPath) + "/" + relativePath);
	}
}

DriveTransfer::DriveTransfer(std::string sourcePath, std::vector<std::string> destinationPaths)
{
	_sourcePath = sourcePath;
	_destinationPaths = destinationPaths;
}

int DriveTransfer::GetProgressPercentage()
{
	return 0;
}

std::string DriveTransfer::GetTaskDescription()
{
	return "Drive Transfer";
}

std::string DriveTransfer::GetSubTaskDescription()
{
	return "Copying X";
}

void DriveTransfer::Execute()
{
	OC_LOG_INFO("Copying started");

	QStorageInfo storageInfo("G:\\");
	if (storageInfo.isValid() && storageInfo.isReady())
	{
		QString path = storageInfo.rootPath();
		qint64 freeSpace = storageInfo.bytesFree();
		qint64 blockSize = storageInfo.blockSize();
	}

	std::string destination = _destinationPaths[0];

	// TODO: Add handling of multiple destinations
	ReplicateFolderStructure(_sourcePath, destination);

	QStringList fileList;

	QDirIterator it(QString::fromStdString(_sourcePath), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext())
	{
		it.next();
		// TODO: Implement
		fileList << it.filePath();

		QString relativePath = it.filePath();
		relativePath = relativePath.mid(static_cast<int>(_sourcePath.length()));
		QFile source(it.filePath());

		// TODO: Ensure trailing slash to remove need of appending it in multiple places
		if (QFile::exists(QString::fromStdString(destination) + relativePath))
		{
			QFile::remove(QString::fromStdString(destination) + "/" + relativePath);
		}

		QFile to(QString::fromStdString(destination) + "/" + relativePath);
	
		OC_LOG_INFO("From: " + source.fileName().toStdString() + " To: " + to.fileName().toStdString());
		source.open(QIODevice::ReadOnly);
		to.open(QIODevice::WriteOnly);

		int TRANSFER_BLOCK_SIZE = 1024 * 1024; // 1MB
		
		int progressBlock = source.size() / 100;
		int progressCount = 0;
		int progress = 0;

		// TODO: Error handling
		QByteArray buffer;
		while(!source.atEnd())
		{
			buffer = source.read(TRANSFER_BLOCK_SIZE);
			to.write(buffer, buffer.size());

			progressCount += buffer.size();
			if(progressCount > progressBlock + (progressBlock * progress))
			{
				progress++;

				emit copyProgressChanged(progress);
			}
		}

//		if (!QFile::copy(source.fileName(), to.fileName()))
//		{
//			OC_LOG_INFO("Copying failed. Error: " + to.errorString().toStdString());
//		}
	}

	OC_LOG_INFO("Copying finished");
}

void DriveTransfer::progressChanged(qint64 progress)
{
	int i = 0;

	emit copyProgressChanged(progress);
}
