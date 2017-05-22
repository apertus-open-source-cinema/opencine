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
