#include <iostream>
#include <memory>

#include <OCui.h>

#include "Presenters/BackupPresenter.h"
#include "Views/BackupView.h"

class OCBackup : public OCui::GUIApplication
{
    std::shared_ptr<IBackupView> _view;
    std::shared_ptr<BackupPresenter> _presenter;

public:
    OCBackup(int argc, char** argv) : GUIApplication(argc, argv, "OCBackup"),
        _view(std::make_shared<BackupView>()),
        _presenter(std::make_shared<BackupPresenter>(*_view))
    {
        SetLayout(*_view.get());
    }
};

int main(int argc, char** argv)
{
    std::shared_ptr<OCBackup> backup = std::make_shared<OCBackup>(argc, argv);
    return backup->Run();
}
