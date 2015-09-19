#include <iostream>
#include <memory>

#include "OCBackup.h"

OCBackup::OCBackup(int argc, char **argv) : GUIApplication(argc, argv, "OCBackup")
{
    _applicationController = std::make_shared<ApplicationController>();

    SetLayout(*_applicationController->GetView());
}

int main(int argc, char** argv)
{
    std::shared_ptr<OCBackup> backup = std::make_shared<OCBackup>(argc, argv);
    backup->Run();

    return 0;
}

