#include "DriveTransfer.h"
#include <QDirIterator>
#include "Log/Logger.h"

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

void DriveTransfer::Execute()
{
	OC_LOG_INFO("Copying started");

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
		if (!QFile::copy(source.fileName(), to.fileName()))
		{
			OC_LOG_INFO("Copying failed. Error: " + to.errorString().toStdString());
		}
	}

	OC_LOG_INFO("Copying finished");
}
