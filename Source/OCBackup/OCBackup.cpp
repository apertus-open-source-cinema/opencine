#include <iostream>
#include <memory>

#include "OCBackup.h"

int main(int argc, char** argv)
{
    std::shared_ptr<OCBackup> backup = std::make_shared<OCBackup>(argc, argv);
    backup->Run();

    return 0;
}

