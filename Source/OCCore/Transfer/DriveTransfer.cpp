#include "DriveTransfer.h"
#include <QDirIterator>
#include "Log/Logger.h"
#include <QStorageInfo>

void DriveTransfer::ReplicateFolderStructure(std::string& rootPath, std::string& targetPath) const
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

DriveTransfer::DriveTransfer(std::string sourcePath, std::vector<std::string> destinationPaths) :
	_sourcePath(sourcePath),
	_destinationPaths(destinationPaths)
{
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

void DriveTransfer::TransferFile(QString sourcePath, QString targetPath)
{
	QString relativePath = sourcePath;
	relativePath = relativePath.mid(3); // e.g. C:/

	QFile source(sourcePath);

	// TODO: Ensure trailing slash to remove need of appending it in multiple places
	if (QFile::exists(targetPath + relativePath))
	{
		QFile::remove(targetPath + "/" + relativePath);
	}

	QFile target(targetPath + "/" + relativePath);

	OC_LOG_INFO("From: " + source.fileName().toStdString() + " To: " + target.fileName().toStdString());
	source.open(QIODevice::ReadOnly);
	if (source.error())
	{
		int i = 0;
	}
	target.open(QIODevice::WriteOnly);
	if (target.error())
	{
		int i = 0;
	}

	int TRANSFER_BLOCK_SIZE = 1024 * 1024; // 1MB

	int progressBlock = source.size() / 100;
	int totalRead = 0;
	int progress = 0;

	// TODO: Error handling
	//QByteArray buffer;
	char* buffer = new char[TRANSFER_BLOCK_SIZE];
	while (!source.atEnd())
	{
		qint64 readSize = source.read(buffer, TRANSFER_BLOCK_SIZE);
		target.write(buffer, readSize);

		totalRead += readSize;
		if (totalRead > progressBlock + (progressBlock * progress))
		{
			progress++;

			ProgressChanged(progress);
		}
	}
}

void DriveTransfer::Execute(/*std::string sourcePath, std::vector<std::string> destinationPaths*/)
{
	OC_LOG_INFO("Copying started");

	std::ostringstream threadID;
	threadID << std::this_thread::get_id();
	QString t = QString("Transfer thread ID: %1").arg(QString::fromStdString(threadID.str()));
	qDebug(t.toLatin1());

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

		TransferFile(it.filePath(), QString::fromStdString(destination));

		//TransferFile(source, target);
		//std::thread transferThread(&DriveTransfer::TransferFile, this, it.filePath(), QString::fromStdString(destination));
		//transferThread.join();
		//std::thread transferThread([this] { TransferFile(*source, *target) });
		//transferThread.join();

		//		if (!QFile::copy(source.fileName(), to.fileName()))
		//		{
		//			OC_LOG_INFO("Copying failed. Error: " + to.errorString().toStdString());
		//		}
	}

	OC_LOG_INFO("Copying finished");
}

void DriveTransfer::ProgressChanged(int progress)
{
	int i = 0;

	std::ostringstream threadID;
	threadID << std::this_thread::get_id();
	QString t = QString("Transfer thread ID: %1").arg(QString::fromStdString(threadID.str()));
	qDebug(t.toLatin1());

	emit CopyProgressChanged(progress);
}

//void DriveTransfer::Execute(std::string sourcePath, std::vector<std::string> destinationPaths)
//{
//}
