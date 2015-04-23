#ifndef CLIPMANAGERLAYOUT_H
#define CLIPMANAGERLAYOUT_H

#include <QWidget>

namespace Ui {
class ClipManagerLayout;
}

class ClipManagerLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ClipManagerLayout(QWidget *parent = 0);
    ~ClipManagerLayout();

private:
    Ui::ClipManagerLayout *ui;
};

#endif // CLIPMANAGERLAYOUT_H
