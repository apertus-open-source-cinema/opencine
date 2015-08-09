#include "OCBackup.h"

#include <iostream>
#include <memory>

#include <OCui.h>

#include "Presenters/BackupPresenter.h"
#include "Views/BackupView.h"

class OCBackup : public OCui::GUIApplication
{
    //std::shared_ptr<QWidget> _layout;
    std::shared_ptr<BackupPresenter> _presenter;
    std::shared_ptr<IBackupView> _view;

public:
    OCBackup(int argc, char** argv) : GUIApplication(argc, argv, "OCBackup")
    {
        _view = std::make_shared<BackupView>();
        _presenter = std::make_shared<BackupPresenter>(*_view);
        //_layout = std::make_shared<BackupLayout>(nullptr, _presenter.get());

        SetLayout(*_view.get());
    }
};

int main(int argc, char** argv)
{
    std::shared_ptr<OCBackup> backup = std::make_shared<OCBackup>(argc, argv);
    return backup->Run();
}
