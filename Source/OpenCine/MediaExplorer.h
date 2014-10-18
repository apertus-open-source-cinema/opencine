#ifndef MEDIAEXPLORER_H
#define MEDIAEXPLORER_H

#include <QWidget>

namespace Ui {
class MediaExplorer;
}

class MediaExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit MediaExplorer(QWidget *parent = 0);
    ~MediaExplorer();

private:
    Ui::MediaExplorer *ui;
};

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString fps READ fps WRITE setFPS NOTIFY fpsChanged)

public:
    DataObject(QObject *parent=0);
    DataObject(const QString &name, const QString &fps, QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QString fps() const;
    void setFPS(const QString &fps);

signals:
    void nameChanged();
    void fpsChanged();

private:
    QString _name;
    QString _FPS;
};


#endif // MEDIAEXPLORER_H
