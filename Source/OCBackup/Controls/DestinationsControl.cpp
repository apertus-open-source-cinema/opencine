// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "DestinationsControl.h"
#include "ui_DestinationsControl.h"

DestinationsControl::DestinationsControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DestinationsControl)
{
    ui->setupUi(this);

    _qmlContext = ui->destinationsListControl->rootContext();
    _qmlContext->setContextProperty("destinationsList", QVariant::fromValue(QList<QObject*>()));
    ui->destinationsListControl->setSource(QUrl("./Widgets/DestinationsList.qml"));

    SetupSignals();
}

DestinationsControl::~DestinationsControl()
{
    delete ui;
}

void DestinationsControl::SetDestinationList(QList<QObject*> destinationList)
{
    _qmlContext->setContextProperty("destinationsList", QVariant::fromValue(destinationList));
}

void DestinationsControl::SetupSignals()
{
    connect(ui->AddDestinationButton, SIGNAL(clicked()), this, SIGNAL(AddDestinationClicked()));
}
