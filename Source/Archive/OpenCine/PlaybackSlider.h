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

    void SetupEvents();
private:
  Ui::PlaybackSlider *ui;
  PlaybackPresenter* _presenter;

private slots:
  void OnSessionChanged(OCSession* session);
  void OnFrameChanged(unsigned int frameNumber, OCFrame* frame);
  void OnSliderMoved(int frameNumber);

  void OnPlayButtonToggled(bool toggled);
  void OnPlayRevButtonToggled(bool toggled);

  void OnStopClicked();
};

#endif // PLAYBACKSLIDER_H
