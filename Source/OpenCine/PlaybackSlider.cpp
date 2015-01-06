#include "PlaybackSlider.h"
#include "ui_PlaybackSlider.h"

PlaybackSlider::PlaybackSlider(PlaybackPresenter* presenter, QWidget *parent) :
QWidget(parent),
ui(new Ui::PlaybackSlider)
{
  ui->setupUi(this);

  _presenter = presenter;

  connect(_presenter, SIGNAL(SessionChanged(OCSession*)), this, SLOT(OnSessionChanged(OCSession*)));
  connect(_presenter, SIGNAL(FrameChanged(unsigned int, OCFrame*)), this, SLOT(OnFrameChanged(unsigned int, OCFrame*)));

  connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderMoved(int)));

  //connect(ui->playButton, SIGNAL(clicked()), _presenter, SLOT(Play()));
  connect(ui->playButton, SIGNAL(toggled(bool)), this, SLOT(OnPlayButtonToggled(bool)));
  connect(ui->playRevButton, SIGNAL(toggled(bool)), this, SLOT(OnPlayRevButtonToggled(bool)));

  connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(OnStopClicked()));

  connect(ui->prevFrameButton, SIGNAL(clicked()), _presenter, SLOT(PrevFrame()));
  connect(ui->nextFrameButton, SIGNAL(clicked()), _presenter, SLOT(NextFrame()));

  connect(ui->jumpStartButton, SIGNAL(clicked()), _presenter, SLOT(JumpToStart()));
  connect(ui->jumpEndButton, SIGNAL(clicked()), _presenter, SLOT(JumpToEnd()));
}

PlaybackSlider::~PlaybackSlider()
{
  delete ui;
}

void PlaybackSlider::OnSessionChanged(OCSession* session)
{
  int i = 0;

  ui->horizontalSlider->setRange(0, session->GetFrameCount());
}

void PlaybackSlider::OnFrameChanged(unsigned int frameNumber, OCFrame* frame)
{
  ui->horizontalSlider->setSliderPosition(frameNumber);
}

void PlaybackSlider::OnSliderMoved(int frameNumber)
{
  disconnect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderMoved(int)));

  _presenter->SetFrame(frameNumber);
  connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderMoved(int)));
}

void PlaybackSlider::OnPlayButtonToggled(bool toggled)
{
  if(toggled)
  {
    ui->playRevButton->setChecked(false);
    _presenter->Play();
  }
  else
  {
    _presenter->Pause();
  }
}

void PlaybackSlider::OnPlayRevButtonToggled(bool toggled)
{
  if(toggled)
  {
    ui->playButton->setChecked(false);
    _presenter->PlayRev();
  }
  else
  {
    _presenter->Pause();
  }
}

void PlaybackSlider::OnStopClicked()
{
  ui->playButton->setChecked(false);
  ui->playRevButton->setChecked(false);

  _presenter->Stop();
}
