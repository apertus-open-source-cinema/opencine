#ifndef PLAYBACKPRESENTER_H
#define PLAYBACKPRESENTER_H

#include <Context.h>
#include <QObject>

class PlaybackPresenter : public QObject
{
    Q_OBJECT

public:
    PlaybackPresenter(OCContext* context);
    ~PlaybackPresenter();

private:
    OCContext* _context;

private slots:
    void UpdateViews();
    void OnSessionChanged();
};

#endif //PLAYBACKPRESENTER_H
