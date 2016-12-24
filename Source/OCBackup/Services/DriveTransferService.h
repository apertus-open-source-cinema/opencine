#ifndef DRIVETRANSFERSERVICE_H
#define DRIVETRANSFERSERVICE_H

#include <thread>

#include "OCService.h"
#include "Transfer/DriveTransfer.h"
#include <QThread>
#include <sstream>

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

		DriveTransfer* driveTransfer = new DriveTransfer(transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths());

		RegisterNewTaskEvent newTaskEvent(driveTransfer);
		GetEventBus()->FireEvent<RegisterNewTaskEvent>(newTaskEvent);

		std::ostringstream threadID;
		threadID << std::this_thread::get_id();
		QString t = QString("Main thread ID: %1").arg(QString::fromStdString(threadID.str()));
		qDebug(t.toLatin1());

		QThread* thread = new QThread();
		driveTransfer->moveToThread(thread);
		connect(thread, SIGNAL(started()), driveTransfer, SLOT(Execute()));
		thread->start();
		//driveTransfer.Execute(transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths());

		//std::thread transferThread(&DriveTransfer::Execute, &driveTransfer, transferEvent.GetSourcePath(), transferEvent.GetDestinationPaths());
		//std::thread::id threadID = transferThread.get_id();
		//transferThread.join();
		//std::thread transferThread([this] { TransferFile(*source, *target) });
		//transferThread.detach();
	}

	//void TestThread(DriveTransfer& driveTransfer) const;
};

//inline void DriveTransferService::TestThread(DriveTransfer& driveTransfer) const
//{
//	driveTransfer.Execute();
//}

#endif //DRIVETRANSFERSERVICE_H
