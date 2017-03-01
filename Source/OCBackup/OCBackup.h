#ifndef OCBACKUP_H
#define OCBACKUP_H

#include <OCui.h>

#include "Presenters/BackupPresenter.h"
#include "Views/BackupView.h"
#include "Services/DriveTransferService.h"

class OCBackup : public OCui::GUIApplication
{
	Q_OBJECT

	std::shared_ptr<IBackupView> _view;
	//std::shared_ptr<IBackupPresenter> _presenter;
	BackupPresenter* _presenter;

	std::shared_ptr<ProgressDialog> _progressDialog;
	std::shared_ptr<ProgressDialogPresenter> _progressDialogPresenter;

	OCEventBus* _bus;

	DriveTransferService* _transferService;

public:
	OCBackup(int& argc, char** argv);
	~OCBackup();
};

#endif //OCBACKUP_H
