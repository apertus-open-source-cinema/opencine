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

  connect(ui->pushButton_2, SIGNAL(clicked()), _presenter, SLOT(Play()));
  connect(ui->pushButton, SIGNAL(clicked()), _presenter, SLOT(Stop()));
}

PlaybackSlider::~PlaybackSlider()
{
    delete ui;
}

void PlaybackSlider::OnSessionChanged(OCSession* session)
{
    int i = 0;

    ui->horizontalSlider->setMaximum(session->GetFrameCount());
}

void PlaybackSlider::OnFrameChanged(unsigned int frameNumber, OCFrame* frame)
{
  ui->horizontalSlider->setSliderPosition(frameNumber);
}
