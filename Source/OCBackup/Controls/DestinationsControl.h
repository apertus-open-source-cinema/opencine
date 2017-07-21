// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef DESTINATIONSCONTROL_H
#define DESTINATIONSCONTROL_H

#include <QQmlContext>
#include <QWidget>

namespace Ui {
    class DestinationsControl;
}

class DestinationsControl : public QWidget
{
    Q_OBJECT

    QList<QObject*> _destinationList;
    QQmlContext* _qmlContext = nullptr;

    void SetupSignals();

public:
    explicit DestinationsControl(QWidget *parent = 0);
    ~DestinationsControl();
    void SetDestinationList(QList<QObject *> destinationList);

signals:
    void AddDestinationClicked();

private:
    Ui::DestinationsControl *ui;
};

#endif // DESTINATIONSCONTROL_H
