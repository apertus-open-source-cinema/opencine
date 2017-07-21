// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCLauncher
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "OCLauncher.h"

#include <iostream>
#include <memory>

#include <OCui.h>

#include "Views/LauncherView.h"

OCLauncher::OCLauncher(int& argc, char** argv) : GUIApplication(argc, argv, "OCLauncher")
{
    _view = std::make_shared<LauncherView>();
    _presenter = std::make_shared<LauncherPresenter>(*_view);

    SetLayout(*static_cast<QWidget*>(_view.get()));

    SetWindowOptions(true);
    Show();
}

int main(int argc, char** argv)
{
	std::cout << "OCLauncher" << std::endl;

    OCLauncher* app = new OCLauncher(argc, argv);
    app->Run();

    if (app != nullptr)
    {
        delete app;
    }

	return 0;
}

