#ifndef MEDIAEXPLORER_H
#define MEDIAEXPLORER_H

#include "MediaExplorerPresenter.h"

#include <QWidget>
#include <QQmlContext>

namespace Ui {
class MediaExplorerView;
}

class MediaExplorerView : public QWidget
{
    Q_OBJECT

public:
    explicit MediaExplorerView(MediaExplorerPresenter* presenter, QWidget *parent = 0);
    ~MediaExplorerView();

private:
    Ui::MediaExplorerView *ui;
    MediaExplorerPresenter* _presenter;

    QQmlContext *qmlContext;
    QList<QObject*> dataList;

private slots:
    void NewClipsFound(ClipInfo*);
};

#include <QObject>
#include <QDebug>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString clipName READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(unsigned int clipWidth READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(unsigned int clipHeight READ height WRITE setHeight NOTIFY heightChanged)

public:
    DataObject(QObject *parent=0);
    DataObject(const QString &name, const unsigned int& width, const unsigned int& height, QObject* parent = 0);

    QString name() const;
    void setName(const QString &name);

    unsigned int width() const;
    void setWidth(const unsigned int &width);

    unsigned int height() const;
    void setHeight(const unsigned int &height);


    //QString fps() const;
    //void setFPS(const QString &fps);

signals:
    void nameChanged();
    void widthChanged();
    void heightChanged();

    //void fpsChanged();

private:
    QString _name;
    unsigned int _width;
    unsigned int _height;
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
