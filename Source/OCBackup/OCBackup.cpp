#include <iostream>
#include <memory>

#include <OCui.h>
#include <OCCore.h>

#include "OCBackup.h"

#include "Presenters/BackupPresenter.h"
#include "Layouts/BackupLayout.h"

class OCBackup : public OCui::GUIApplication
{
    std::shared_ptr<QWidget> _layout;
    std::shared_ptr<IBackupPresenter> _presenter;

public:
    OCBackup(int argc, char** argv) : GUIApplication(argc, argv, "OCBackup")
    {
        _presenter = std::make_shared<BackupPresenter>();
        _layout = std::make_shared<OCBackupLayout>(nullptr, _presenter.get());
        _layout->showFullScreen();
        SetLayout(*_layout.get());
    }
};

int main(int argc, char** argv)
{
    std::shared_ptr<OCBackup> backup = std::make_shared<OCBackup>(argc, argv);
    return backup->Run();
}
