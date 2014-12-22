#ifndef PLAYBACKSLIDER_H
#define PLAYBACKSLIDER_H

#include "Presenter/PlaybackPresenter.h"


#include <QWidget>

namespace Ui {
  class PlaybackSlider;
}

class PlaybackSlider : public QWidget
{
  Q_OBJECT

public:
  explicit PlaybackSlider(PlaybackPresenter* presenter, QWidget *parent = 0);
  ~PlaybackSlider();

private:
  Ui::PlaybackSlider *ui;
  PlaybackPresenter* _presenter;

private slots:
  void OnSessionChanged();
  void OnFrameChanged(unsigned int frameNumber);
};

#endif // PLAYBACKSLIDER_H
