#ifndef DESTINATIONSCONTROL_H
#define DESTINATIONSCONTROL_H

#include <QWidget>

namespace Ui {
class DestinationsControl;
}

class DestinationsControl : public QWidget
{
    Q_OBJECT

    void SetupSignals();

public:
    explicit DestinationsControl(QWidget *parent = 0);
    ~DestinationsControl();

signals:
    void AddDestinationClicked();

private:
    Ui::DestinationsControl *ui;
};

#endif // DESTINATIONSCONTROL_H
