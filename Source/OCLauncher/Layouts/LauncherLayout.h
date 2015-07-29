#ifndef LAUNCHERLAYOUT_H
#define LAUNCHERLAYOUT_H

#include <QWidget>

namespace Ui {
class LauncherLayout;
}

class LauncherLayout : public QWidget
{
    Q_OBJECT

public:
    explicit LauncherLayout(QWidget *parent = 0);
    ~LauncherLayout();

private:
    Ui::LauncherLayout *ui;
};

#endif // LAUNCHERLAYOUT_H
