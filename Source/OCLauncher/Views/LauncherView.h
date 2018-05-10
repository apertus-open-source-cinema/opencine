// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCLauncher
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef LAUNCHERLAYOUT_H
#define LAUNCHERLAYOUT_H

#include <QWidget>

#include "Interfaces/ILauncherView.h"

namespace Ui {
    class LauncherView;
}

class LauncherView : public ILauncherView
{
	Q_OBJECT

    Ui::LauncherView *ui;

    void InsertButton(QString name, QString image);

public:
    explicit LauncherView(QWidget *parent = nullptr);
    ~LauncherView();

    void SetButtonList(std::vector<ApplicationInfo> list) override;
};

#endif // LAUNCHERLAYOUT_H
