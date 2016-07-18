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
