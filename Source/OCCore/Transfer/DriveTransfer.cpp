#include "DriveTransfer.h"
#include <QDirIterator>
#include "Log/Logger.h"

DriveTransfer::DriveTransfer()
{
}

void DriveTransfer::ReplicateFolderStructure(std::string rootPath, std::string targetPath) const
{
	QDir().mkdir(QString::fromStdString(targetPath));

	QDirIterator directories(QString::fromStdString(rootPath), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

	while (directories.hasNext())
	{
		directories.next();
		

		QString relativePath = directories.filePath();
		relativePath = relativePath.mid(rootPath.length());
		QDir().mkdir(QString::fromStdString(targetPath) + relativePath);
	}
}

void DriveTransfer::StartTransfer()
{
	OC_LOG_INFO("Copying started");

	std::string rootPath = "D:/Temp/Test_Folder";
	std::string targetPath = "D:/Temp/Test_Folder_TARGET";

	ReplicateFolderStructure(rootPath, targetPath);


	QStringList fileList;

	QDirIterator it(QString::fromStdString(rootPath), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext())
	{
		it.next();
		// TODO: Implement
		fileList << it.filePath();



		//connect(&to, SIGNAL(bytesWritten(qint64)), this, SLOT(onWrite(qint64)));
		QString relativePath = it.filePath();
		relativePath = relativePath.mid(rootPath.length());
		QFile source(it.filePath());

		if(QFile::exists(QString::fromStdString(targetPath) + relativePath))
		{
			//QFile::remove(QString::fromStdString(targetPath) + relativePath);
		}

		QFile to(QString::fromStdString(targetPath) + relativePath);
		//source.copy(to.fileName());
	}

	OC_LOG_INFO("Copying finished");
}
