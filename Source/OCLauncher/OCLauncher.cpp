#include <iostream>
#include <memory>

#include <OCui.h>

#include "OCLauncher.h"

class OCLauncher : public OCui::GUIApplication
{
public:
    OCLauncher(int argc, char** argv) : GUIApplication(argc, argv, "OCLauncher")
    {

    }
};

int main(int argc, char** argv)
{
    std::cout << "OCLauncher" << std::endl;

    std::shared_ptr<OCLauncher> backup = std::make_shared<OCLauncher>(argc, argv);
    backup->Run();

    return 0;
}
