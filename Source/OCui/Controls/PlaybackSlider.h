#ifndef PLAYBACKSLIDER_H
#define PLAYBACKSLIDER_H

#include <QWidget>

#include "OCui_export.h"

namespace Ui {
  class PlaybackSlider;
}

class EXPORT_API PlaybackSlider : public QWidget
{
  Q_OBJECT

public:
  explicit PlaybackSlider(QWidget *parent = 0);
  ~PlaybackSlider();

    void SetupEvents();
private:
  Ui::PlaybackSlider *ui;

private slots:
  //void OnSessionChanged(OCSession* session);
  //void OnFrameChanged(unsigned int frameNumber, OCFrame* frame);
  //void OnSliderMoved(int frameNumber);

  //void OnPlayButtonToggled(bool toggled);
  //void OnPlayRevButtonToggled(bool toggled);

  //void OnStopClicked();
};

#endif // PLAYBACKSLIDER_H
