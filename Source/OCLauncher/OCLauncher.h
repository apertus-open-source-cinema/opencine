#ifndef OCLAUNCHER_H
#define OCLAUNCHER_H

#include "OCui.h"

class OCLauncher : public OCui::GUIApplication
{
    std::shared_ptr<QWidget> _layout;

public:
    OCLauncher(int argc, char** argv);
};

#endif //OCLAUNCHER_H
