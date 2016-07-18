#include "DestinationsControl.h"
#include "ui_DestinationsControl.h"


QQmlContext*  qmlContext;

DestinationsControl::DestinationsControl(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DestinationsControl)
{
	ui->setupUi(this);

	ui->destinationsListControl->setSource(QUrl("./Widgets/DestinationsList.qml"));
	//qmlContext = ui->destinationsListControl->rootContext();

	SetupSignals();
}

DestinationsControl::~DestinationsControl()
{
	delete ui;
}

void DestinationsControl::SetDestinationList(std::vector<QString> destinationList)
{
	//_destinationList->clear();

	//for (auto& destination : destinationList)
	//{
	//	_destinationList->append(destination);
	//}

	//qmlContext->setContextProperty("fileList", QVariant::fromValue(_destinationList));
}

void DestinationsControl::SetupSignals()
{
	connect(ui->AddDestinationButton, SIGNAL(clicked()), this, SIGNAL(AddDestinationClicked()));
}