#ifndef DRIVETRANSFERSERVICE_H
#define DRIVETRANSFERSERVICE_H

#include <thread>
#include <fstream>
#include <sstream>
#include <queue>

#include <QThread>

#include "OCService.h"
#include "Transfer/DriveTransfer.h"
#include <Hash/xxHashAdapter.h>
#include "Task/HashCheckTask.h"

// TODO: Refactor by moving to more suitable location and possibly renaming, possible location OCCore/Service
// Note: std::string is used instead of QString, see previous note
class IDriveTransferService : public OCService
{
	Q_OBJECT


public:
	IDriveTransferService(OCEventBus* bus) : OCService(bus)
	{
	}

	virtual ~IDriveTransferService()
	{
	}

	virtual void SetSourceDrive(std::string sourceDrive) = 0;
	virtual void SetDestinationDrives(std::vector<std::string> destinationDrives) = 0;
};

class DriveTransferService : public IDriveTransferService
{
	Q_OBJECT
	
	std::vector<FileTransferInfo> fileList;

public:
	DriveTransferService(OCEventBus* bus) : IDriveTransferService(bus)
	{
		GetEventBus()->RegisterEventHandler<StartDriveTransferEvent, DriveTransferService>(std::bind(&DriveTransferService::StartDriveTransferEventHandler, this, std::placeholders::_1));
	}

	void SetSourceDrive(std::string sourceDrive) override
	{
	}

	void SetDestinationDrives(std::vector<std::string> destinationDrives) override
	{
	}

	bool Execute()
	{
		bool finished = false;

		return finished;
	}

	void StartDriveTransferEventHandler(const OCEvent& event)
	{
		// TODO: Conversion is necessary at the moment, as arguments are not polymorphic yet
		const StartDriveTransferEvent transferEvent = dynamic_cast<const StartDriveTransferEvent&>(event);


		EnumerateFiles(QString::fromStdString(transferEvent.GetSourcePath()), &fileList);

		ReplicateFolderStructure(transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths().at(0));

		DriveTransfer* driveTransfer = new DriveTransfer(transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths(), fileList);

		RegisterNewTaskEvent newTaskEvent(driveTransfer);
		GetEventBus()->FireEvent<RegisterNewTaskEvent>(newTaskEvent);

		QThread* thread = thread = new QThread();
		driveTransfer->moveToThread(thread);
		connect(thread, SIGNAL(started()), driveTransfer, SLOT(Execute()));
		connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));		
		qRegisterMetaType<int64_t>("int64_t");
		connect(driveTransfer, SIGNAL(FileTransfered(int, int64_t)), this, SLOT(FileTransfered(int, int64_t)));
		connect(driveTransfer, SIGNAL(TransferFinished()), this, SLOT(TransferFinished()));
		thread->start();


		//TODO: Implement steps
		//Step 1: Connect to FileCopied() signal of the transfer task
		//Step 2: When a file was transfered get the checksum and location
		//Step 3: Start validation task in new thread, some sort of queue and synchronization is required to prevent race conditions and dead locks


		//		std::ostringstream threadID;
		//		threadID << std::this_thread::get_id();
		//		QString t = QString("Main thread ID: %1").arg(QString::fromStdString(threadID.str()));
		//		qDebug(t.toLatin1());

		/*QString*/


		/*QFile file(targetFile);
		file.open(QIODevice::WriteOnly);
		QDataStream stream(&file);*/


		// TODO: Comment in again, after checksum comparison module is ready
		//		QThread* thread = new QThread();
		//		driveTransfer->moveToThread(thread);
		//		connect(thread, SIGNAL(started()), driveTransfer, SLOT(Execute()));
		//		thread->start();


		//std::shared_ptr<ITask> hashCheckTask = std::make_shared<HashCheckTask>();




		//driveTransfer.Execute(transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths());

		//std::thread transferThread(&DriveTransfer::Execute, &driveTransfer, transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths());
		//std::thread::id threadID = transferThread.get_id();
		//transferThread.join();
		//std::thread transferThread([this] { TransferFile(*source, *target) });
		//transferThread.detach();
	}

	//void TestThread(DriveTransfer& driveTransfer) const;

	void ReplicateFolderStructure(std::string& rootPath, std::string& targetPath) const
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

	// Used to enumerate files in source folder, usually source drive
	void EnumerateFiles(QString path, std::vector<FileTransferInfo>* fileList)
	{
		QDir dir(path);
		QDirIterator files(path, QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files, QDirIterator::Subdirectories);

		while (files.hasNext())
		{
			files.next();

			FileTransferInfo fileInfo;
			fileInfo.FileName = files.fileName().toLatin1();
			QString relativeFolder = dir.relativeFilePath(files.filePath());
			int relativePathLength = relativeFolder.length() - fileInfo.FileName.length();
			relativeFolder = relativeFolder.left(relativePathLength);
			fileInfo.RelativeFolderPath = relativeFolder.toStdString(); //files.fileInfo().path().toLatin1();
			fileList->push_back(fileInfo);

			//int i = 0;
			//std::string fileName = files.fileName().toStdString();
			qDebug(files.fileName().toLatin1());// std::cout << fileName << std::endl;
			qDebug(files.filePath().toLatin1());
			qDebug(files.fileInfo().path().toLatin1());
			qDebug(dir.relativeFilePath(files.filePath()).toLatin1());


			//QString relativePath = directories.filePath();
			//relativePath = relativePath.mid(static_cast<int>(rootPath.length()));
			//QDir().mkdir(QString::fromStdString(targetPath) + "/" + relativePath);
		}
	}

	private slots:
	void FileTransfered(int index, int64_t checksum)
	{
		fileList.at(index).Checksum = checksum;
	}

	void TransferFinished()
	{
		for (FileTransferInfo transferInfo : fileList)
		{
			// CHECKSUM!!!
			std::string filePath = "E:/Temp/OC_COPY/" + transferInfo.RelativeFolderPath + transferInfo.FileName;
			HashCheckTask* hashCheckTask = new HashCheckTask(/*transferEvent.GetDestinationPaths().at(0)*/ filePath);
			RegisterNewTaskEvent hashTaskEvent(hashCheckTask);
			GetEventBus()->FireEvent<RegisterNewTaskEvent>(hashTaskEvent);
			QThread* thread = new QThread();
			hashCheckTask->moveToThread(thread);
			connect(thread, SIGNAL(started()), hashCheckTask, SLOT(Execute()));
			connect(hashCheckTask, SIGNAL(HashChecked(int64_t)), this, SLOT(HashChecked(int64_t)));
			thread->start();
		}
	}

	void HashChecked(int64_t checksum)
	{
		int i = 0;
	}
};

//inline void DriveTransferService::TestThread(DriveTransfer& driveTransfer) const
//{
//	driveTransfer.Execute();
//}


#endif //DRIVETRANSFERSERVICE_H
