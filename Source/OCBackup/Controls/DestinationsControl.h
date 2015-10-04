#ifndef DESTINATIONSCONTROL_H
#define DESTINATIONSCONTROL_H

#include <QWidget>

namespace Ui {
class DestinationsControl;
}

class DestinationsControl : public QWidget
{
    Q_OBJECT

public:
    explicit DestinationsControl(QWidget *parent = 0);
    ~DestinationsControl();

private:
    Ui::DestinationsControl *ui;
};

#endif // DESTINATIONSCONTROL_H
