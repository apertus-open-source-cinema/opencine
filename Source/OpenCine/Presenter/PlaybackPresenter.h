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
  void PlayRev();

  void Pause();
  void Stop();

  void NextFrame();
  void PrevFrame();

  void JumpToStart();
  void JumpToEnd();

  void SetFrame(unsigned int frameNumber);

private:
  OCContext* _context;
  OCSession *_session;

  QTimer* _timer;

  int _currentFrame;

  float _frameRate;

  void Update();

signals:
  void SessionChanged(OCSession* session);
  void FrameChanged(unsigned int frameNumber, OCFrame* frame);

private slots:
  void OnSessionChanged(OCSession* session);

  void PlayHandler();
  void PlayRevHandler();
};



#endif //PLAYBACKPRESENTER_H
