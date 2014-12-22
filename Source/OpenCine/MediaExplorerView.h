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


class MyClass : public QObject
{
    Q_OBJECT
public slots:
    void cppSlot(const int &clipIndex) {
        qDebug() << "Called the C++ slot with message:" << clipIndex;
    }
};


#endif // MEDIAEXPLORER_H
