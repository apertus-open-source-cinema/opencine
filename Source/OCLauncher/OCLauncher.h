#ifndef OCLAUNCHER_H
#define OCLAUNCHER_H

#include "OCui.h"

#include "Presenters/LauncherPresenter.h"

class OCLauncher : public OCui::GUIApplication
{
    std::shared_ptr<ILauncherView> _view;
    std::shared_ptr<LauncherPresenter> _presenter;

public:
    OCLauncher(int& argc, char** argv);
};

#endif //OCLAUNCHER_H
