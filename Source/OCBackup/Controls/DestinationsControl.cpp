#include "DestinationsControl.h"
#include "ui_DestinationsControl.h"

DestinationsControl::DestinationsControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DestinationsControl)
{
    ui->setupUi(this);

    ui->destinationsListControl->setSource(QUrl("./Widgets/DestinationsList.qml"));
}

DestinationsControl::~DestinationsControl()
{
    delete ui;
}
