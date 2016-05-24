#ifndef DESTINATIONSCONTROL_H
#define DESTINATIONSCONTROL_H

#include <QWidget>

namespace Ui {
	class DestinationsControl;
}

class DestinationsControl : public QWidget
{
	Q_OBJECT

		std::vector<QString> _destinationList;

	void SetupSignals();

public:
	explicit DestinationsControl(QWidget *parent = 0);
	~DestinationsControl();
	void SetDestinationList(std::vector<QString> destinationList);

signals:
	void AddDestinationClicked();

private:
	Ui::DestinationsControl *ui;
};

#endif // DESTINATIONSCONTROL_H
