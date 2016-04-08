#include "DestinationsControl.h"
#include "ui_DestinationsControl.h"

DestinationsControl::DestinationsControl(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DestinationsControl)
{
	ui->setupUi(this);

	ui->destinationsListControl->setSource(QUrl("./Widgets/DestinationsList.qml"));

	SetupSignals();
}

DestinationsControl::~DestinationsControl()
{
	delete ui;
}

void DestinationsControl::SetupSignals()
{
	connect(ui->AddDestinationButton, SIGNAL(clicked()), this, SIGNAL(AddDestinationClicked()));
}