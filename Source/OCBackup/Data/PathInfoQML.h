#ifndef DRIVELISTITEM_H
#define DRIVELISTITEM_H

#include <QObject>

class PathInfoQML : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString path READ path CONSTANT)
    Q_PROPERTY(QString drive READ drive CONSTANT)
    Q_PROPERTY(QString driveName READ driveName CONSTANT)

    Q_PROPERTY(unsigned int usedSpace READ usedSpace CONSTANT)
    Q_PROPERTY(unsigned int totalSpace READ totalSpace CONSTANT)
    Q_PROPERTY(QString spaceUnit READ spaceUnit CONSTANT)

    QString _path;
    QString _drive;
    QString _driveName;

    unsigned int _usedSpace;
    unsigned int _totalSpace;
    QString _spaceUnit;

public:
    PathInfoQML(QString path, QString drive, QString driveName, unsigned int usedSpace, unsigned int totalSpace, QString spaceUnit)
    {
        _path = path;
        _drive = drive;
        _driveName = driveName;

        _usedSpace = usedSpace;
        _totalSpace = totalSpace;
        _spaceUnit = spaceUnit;
    }

    QString path() const
    {
        return _path;
    }

    QString drive() const
    {
        return _drive;
    }

    QString driveName() const
    {
        return _driveName;
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
