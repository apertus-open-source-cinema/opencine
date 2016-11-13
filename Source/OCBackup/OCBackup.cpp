#include <memory>

#include "OCBackup.h"
#include "Services/DriveTransferService.h"

OCBackup::OCBackup(int &argc, char **argv) : OCui::GUIApplication(argc, argv, "OCBackup"),
	_view(std::make_shared<BackupView>())
{
	_bus = new OCEventBus();
	_presenter = new BackupPresenter(*_view, _bus); //std::make_shared<BackupPresenter>(*_view);

	// TODO: Service is initialized manually for now, this has to be changed in the future when a service manager is present
	DriveTransferService* _transferService = new DriveTransferService(_bus);

	_progressDialog = std::make_shared<ProgressDialog>();
	_progressDialogPresenter = std::make_shared<ProgressDialogPresenter>(*_progressDialog.get(), _bus);

	SetLayout(*_view);

	ShowMaximized();
}

OCBackup::~OCBackup()
{
	if(_bus)
	{
		delete _bus;
	}
}

int main(int argc, char** argv)
{
	std::shared_ptr<OCBackup> backup = std::make_shared<OCBackup>(argc, argv);
	backup->Run();

	return 0;
}
