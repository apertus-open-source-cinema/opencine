#include "PlaybackSlider.h"
#include "ui_PlaybackSlider.h"

PlaybackSlider::PlaybackSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaybackSlider),
    _advancedMode(false)
{
    ui->setupUi(this);

    SetupEvents();

    SetupPlayer();
}

void PlaybackSlider::UpdateSlider(qint64 currentPos)
{
    int pos = ui->horizontalSlider->value();
    int max = ui->horizontalSlider->maximum();

    ui->horizontalSlider->setValue(player->position());
}

void PlaybackSlider::SetupEvents()
{
    //    connect(_presenter, SIGNAL(SessionChanged(OCSession*)), SLOT(OnSessionChanged(OCSession*)));
    //    connect(_presenter, SIGNAL(FrameChanged(unsigned int, OCFrame*)), SLOT(OnFrameChanged(unsigned int, OCFrame*)));

    //    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(OnSliderMoved(int)));

    //connect(ui->playButton, SIGNAL(clicked()), SLOT(Play()));
    connect(ui->playButton, SIGNAL(toggled(bool)), SLOT(OnPlayButtonToggled(bool)));
    //    connect(ui->playRevButton, SIGNAL(toggled(bool)), SLOT(OnPlayRevButtonToggled(bool)));

    connect(ui->stopButton, SIGNAL(clicked()), SLOT(OnStopClicked()));

    connect(ui->prevFrameButton, SIGNAL(clicked()), this, SLOT(PrevFrame()));
    connect(ui->nextFrameButton, SIGNAL(clicked()), this, SLOT(NextFrame()));

    connect(ui->jumpStartButton, SIGNAL(clicked()), this, SLOT(OnJumpStartClicked()));
    connect(ui->jumpEndButton, SIGNAL(clicked()), this, SLOT(OnJumpEndClicked()));
    //    connect(ui->jumpStartButton, SIGNAL(clicked()), _presenter, SLOT(JumpToStart()));
    //    connect(ui->jumpEndButton, SIGNAL(clicked()), _presenter, SLOT(JumpToEnd()));
}

void PlaybackSlider::SetupPlayer()
{
    qputenv("QTAV_LOG", "all");
    qputenv("QTAV_LOG_LEVEL", "all");
    qputenv("QTAV_FFMPEG_LOG", "debug");
    QtAV::setLogLevel(QtAV::LogAll);

    QVBoxLayout *vl = new QVBoxLayout(ui->frame);
    vl->setMargin(0);
    QtAV::Widgets::registerRenderers();
    player = new QtAV::AVPlayer(vl);
    QtAV::VideoOutput* videoOutput = new QtAV::VideoOutput(vl);
    if (!videoOutput->widget())
    {
        return;
    }

    player->setRenderer(videoOutput);
    QWidget* widget = videoOutput->widget();
    vl->addWidget(widget);
    //ui->frame->setLayout(vl);
    QPoint pos = widget->pos();
    int width = widget->width();
    int height = widget->height();

    //videoOutput->widget()->showFullScreen();

    player->setSeekType(QtAV::AccurateSeek);
    player->setFile("/media/dev/OC_TEST_DISK2/darklab.mov");
    player->load();

    connect(player, &QtAV::AVPlayer::positionChanged, this, &PlaybackSlider::UpdateSlider);

    connect(player, &QtAV::AVPlayer::started, [this](){
        connect(player, &QtAV::AVPlayer::seekFinished, this, &PlaybackSlider::PauseAfterLoad);
        player->setPosition(0);
        ui->horizontalSlider->setRange(0, player->duration());
    });
    //player->setRelativeTimeMode(false);
    //player->setStopPosition(player->duration());
    player->play();
}

void PlaybackSlider::PrevFrame()
{
    player->stepBackward();
}

void PlaybackSlider::NextFrame()
{
    player->stepForward();
}

void PlaybackSlider::PauseAfterLoad()
{
    player->pause(true);
    disconnect(player, &QtAV::AVPlayer::seekFinished, this, &PlaybackSlider::PauseAfterLoad);
}

PlaybackSlider::~PlaybackSlider()
{
    delete ui;
}

//void PlaybackSlider::OnSessionChanged(OCSession* session)
//{
//  int i = 0;

//  ui->horizontalSlider->setRange(0, session->GetFrameCount());
//}

//void PlaybackSlider::OnFrameChanged(unsigned int frameNumber, OCFrame* frame)
//{
//  ui->horizontalSlider->setSliderPosition(frameNumber);
//}

//void PlaybackSlider::OnSliderMoved(int frameNumber)
//{
//  disconnect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderMoved(int)));

//  _presenter->SetFrame(frameNumber);
//  connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(OnSliderMoved(int)));
//}

void PlaybackSlider::OnPlayButtonToggled(bool toggled)
{
    player->togglePause();

    if(toggled)
    {
        ui->playRevButton->setChecked(false);
    }
}

//void PlaybackSlider::OnPlayRevButtonToggled(bool toggled)
//{
//  if(toggled)
//  {
//    ui->playButton->setChecked(false);
//    _presenter->PlayRev();
//  }
//  else
//  {
//    _presenter->Pause();
//  }
//}

void PlaybackSlider::OnStopClicked()
{
    ui->playButton->setChecked(false);
    ui->playRevButton->setChecked(false);

    player->togglePause();
    player->setState(QtAV::AVPlayer::PausedState);
    player->setPosition(0);
    //_presenter->Stop();
}

void PlaybackSlider::OnJumpStartClicked()
{
    ui->playButton->setChecked(false);
    ui->playRevButton->setChecked(false);

    player->togglePause();
    player->setState(QtAV::AVPlayer::PausedState);
    player->setPosition(0);
}

void PlaybackSlider::OnJumpEndClicked()
{
    ui->playButton->setChecked(false);
    ui->playRevButton->setChecked(false);

    player->togglePause();
    player->setState(QtAV::AVPlayer::PausedState);
    player->setPosition(player->duration());
}

