#ifndef MEDIAEXPLORER_H
#define MEDIAEXPLORER_H

#include "MediaExplorerPresenter.h"

#include <QWidget>

namespace Ui {
class MediaExplorer;
}

class MediaExplorerView : public QWidget
{
    Q_OBJECT

public:
    explicit MediaExplorerView(MediaExplorerPresenter* presenter, QWidget *parent = 0);
    ~MediaExplorerView();

private:
    Ui::MediaExplorer *ui;
    MediaExplorerPresenter* _presenter;
};

#include <QObject>
#include <QDebug>

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

class MyClass : public QObject
{
    Q_OBJECT
public slots:
    void cppSlot(const int &clipIndex) {
        qDebug() << "Called the C++ slot with message:" << clipIndex;
    }
};


#endif // MEDIAEXPLORER_H
