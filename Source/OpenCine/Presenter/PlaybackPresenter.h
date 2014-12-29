#ifndef PLAYBACKPRESENTER_H
#define PLAYBACKPRESENTER_H

#include "Core/Context.h"

#include <Context.h>
#include <QObject>
#include <QTimer>

class PlaybackPresenter : public QObject
{
  Q_OBJECT

public:
  PlaybackPresenter(OCContext* context);
  ~PlaybackPresenter();

public slots:
  void Play();
  void Pause();
  void Stop();

  void NextFrame();
  void PrevFrame();

  void SetFrame(unsigned int frameNumber);

private:
  OCContext* _context;
  OCSession *_session;

  QTimer* _timer;

  int _currentFrame;

  float _frameRate;

signals:
  void SessionChanged(OCSession* session);
  void FrameChanged(unsigned int frameNumber, OCFrame* frame);

private slots:
  //void UpdateViews();
  void OnSessionChanged(OCSession* session);
  void Update();
};



#endif //PLAYBACKPRESENTER_H
