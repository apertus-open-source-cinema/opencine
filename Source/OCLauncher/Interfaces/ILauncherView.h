// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCLauncher
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef ILAUNCHERVIEW_H
#define ILAUNCHERVIEW_H

#include <vector>

#include <QWidget>

struct ApplicationInfo
{
    QString Name;
    QString ImagePath;
};

class ILauncherView : public QWidget
{
public:
    virtual void SetButtonList(std::vector<ApplicationInfo> list) = 0;
};

#endif //ILAUNCHERVIEW_H
