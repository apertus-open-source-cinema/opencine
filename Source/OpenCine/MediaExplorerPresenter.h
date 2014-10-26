#ifndef MEDIAEXPLORERPRESENTER_H
#define MEDIAEXPLORERPRESENTER_H

#include <QObject>
#include <QMessageBox>

class MediaExplorerPresenter : public QObject
{
    Q_OBJECT

public:
    MediaExplorerPresenter();
    ~MediaExplorerPresenter();

private slots:
    void TestMessage();
};

#endif //MEDIAEXPLORERPRESENTER_H
