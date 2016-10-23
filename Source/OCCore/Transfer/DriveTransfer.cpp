#include "DriveTransfer.h"
#include <QDir>
#include <qdiriterator.h>

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
	std::string rootPath = "C:/Temp/Test_Folder";
	std::string targetPath = "C:/Temp/Test_Folder_TARGET";

	ReplicateFolderStructure(rootPath, targetPath);


	QStringList fileList;

	QDirIterator it(QString::fromStdString(rootPath), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext())
	{
		it.next();
		// TODO: Implement
		fileList << it.filePath();
	}
}
