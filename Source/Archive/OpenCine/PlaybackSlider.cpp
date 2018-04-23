#include "PlaybackSlider.h"
#include "ui_PlaybackSlider.h"

PlaybackSlider::PlaybackSlider(PlaybackPresenter* presenter, QWidget *parent) :
QWidget(parent),
ui(new Ui::PlaybackSlider)
{
  ui->setupUi(this);

  _presenter = presenter;

  SetupEvents();
}

void PlaybackSlider::SetupEvents()
{
    connect(_presenter, SIGNAL(SessionChanged(OCSession*)), SLOT(OnSessionChanged(OCSession*)));
    connect(_presenter, SIGNAL(FrameChanged(unsigned int, OCFrame*)), SLOT(OnFrameChanged(unsigned int, OCFrame*)));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(OnSliderMoved(int)));

    //connect(ui->playButton, SIGNAL(clicked()), _presenter, SLOT(Play()));
    connect(ui->playButton, SIGNAL(toggled(bool)), SLOT(OnPlayButtonToggled(bool)));
    connect(ui->playRevButton, SIGNAL(toggled(bool)), SLOT(OnPlayRevButtonToggled(bool)));

    connect(ui->stopButton, SIGNAL(clicked()), SLOT(OnStopClicked()));

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
  connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(OnSliderMoved(int)));
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
