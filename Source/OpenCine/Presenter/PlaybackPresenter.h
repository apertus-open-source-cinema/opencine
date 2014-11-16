#ifndef PLAYBACKPRESENTER_H
#define PLAYBACKPRESENTER_H

#include <QObject>

class PlaybackPresenter : public QObject
{
    Q_OBJECT

public:
    PlaybackPresenter();
    ~PlaybackPresenter();

private slots:
    void UpdateViews();
};

#endif //PLAYBACKPRESENTER_H
