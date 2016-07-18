#ifndef DRIVELISTITEM_H
#define DRIVELISTITEM_H

#include <QObject>

class DriveListItem : public QObject
{
	Q_OBJECT

		Q_PROPERTY(QString driveName READ driveName CONSTANT)
		Q_PROPERTY(QString driveLetter READ driveLetter CONSTANT)

		Q_PROPERTY(unsigned int usedSpace READ usedSpace CONSTANT)
		Q_PROPERTY(unsigned int totalSpace READ totalSpace CONSTANT)
		Q_PROPERTY(QString spaceUnit READ spaceUnit CONSTANT)

		QString _driveName;
	QString _driveLetter;

	unsigned int _usedSpace;
	unsigned int _totalSpace;
	QString _spaceUnit;

public:
	DriveListItem(QString driveName, QString driveLetter, unsigned int usedSpace, unsigned int totalSpace, QString spaceUnit)
	{
		_driveName = driveName;
		_driveLetter = driveLetter;

		_usedSpace = usedSpace;
		_totalSpace = totalSpace;
		_spaceUnit = spaceUnit;
	}

	QString driveName() const
	{
		return _driveName;
	}

	QString driveLetter() const
	{
		return _driveLetter;
	}

	unsigned int totalSpace() const
	{
		return _totalSpace;
	}

	QString spaceUnit() const
	{
		return _spaceUnit;
	}

	unsigned int usedSpace() const
	{
		return _usedSpace;
	}
};

#endif //DRIVELISTITEM_H
