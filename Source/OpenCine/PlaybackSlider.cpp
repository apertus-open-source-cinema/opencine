#include "PlaybackSlider.h"
#include "ui_PlaybackSlider.h"

PlaybackSlider::PlaybackSlider(PlaybackPresenter* presenter, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PlaybackSlider)
{
  ui->setupUi(this);

  _presenter = presenter;

  connect(_presenter, SIGNAL(SessionChanged(OCSession*)), this, SLOT(OnSessionChanged(OCSession*)));
  connect(_presenter, SIGNAL(FrameChanged(unsigned int)), this, SLOT(OnFrameChanged(unsigned int)));
}

PlaybackSlider::~PlaybackSlider()
{
    delete ui;
}

void PlaybackSlider::OnSessionChanged(OCSession*)
{
    int i = 0;

    ui->horizontalSlider->setMaximum(1000);
}

void PlaybackSlider::OnFrameChanged(unsigned int frameNumber)
{

}
