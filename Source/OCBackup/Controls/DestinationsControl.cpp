#include "DestinationsControl.h"
#include "ui_DestinationsControl.h"

DestinationsControl::DestinationsControl(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DestinationsControl)
{
	ui->setupUi(this);

    _qmlContext = ui->destinationsListControl->rootContext();
    _destinationList = new QList<QObject*>();
    _qmlContext->setContextProperty("fileList2", QVariant::fromValue(*_destinationList));
	ui->destinationsListControl->setSource(QUrl("./Widgets/DestinationsList.qml"));

	SetupSignals();
}

DestinationsControl::~DestinationsControl()
{
	delete ui;
}

void DestinationsControl::SetDestinationList(std::vector<DestinationsListItem>& destinationList)
{
    _destinationList->clear();

    for (auto& destination : destinationList)
    {
        _destinationList->push_back(&destination);
    }

    _qmlContext->setContextProperty("fileList2", QVariant::fromValue(*_destinationList));
}

void DestinationsControl::SetupSignals()
{
	connect(ui->AddDestinationButton, SIGNAL(clicked()), this, SIGNAL(AddDestinationClicked()));
}
