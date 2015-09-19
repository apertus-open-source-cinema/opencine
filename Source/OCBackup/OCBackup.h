#ifndef OCBACKUP_H
#define OCBACKUP_H

#include <OCui.h>

#include "Presenters/BackupPresenter.h"
#include "Views/BackupView.h"

class ApplicationController : public QObject
{
    Q_OBJECT

    std::shared_ptr<IBackupView> _view;
    std::shared_ptr<BackupPresenter> _presenter;

    void SetupSignals()
    {
        QObject::connect(_presenter.get(), SIGNAL(StartTransferSig(std::string)), this, SLOT(StartTransfer(std::string)));
    }
public:
    ApplicationController() :
        _view(std::make_shared<BackupView>()),
        _presenter(std::make_shared<BackupPresenter>(*_view))
    {
        SetupSignals();
    }

    IBackupView* GetView()
    {
        return _view.get();
    }

private slots:
    void StartTransfer(std::string drivePath)
    {
        int i = 0;
    }
};

class OCBackup : public OCui::GUIApplication
{
    std::shared_ptr<ApplicationController> _applicationController;

public:
    OCBackup(int argc, char** argv);
};

#endif //OCBACKUP_H
