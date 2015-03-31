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

    QQmlContext* _qmlContext;
    QList<QObject*> _dataList;

private slots:
    void NewClipsFound(ClipInfo*);
    void LoadClip(int clipNumber);
};

#endif // MEDIAEXPLORER_H
