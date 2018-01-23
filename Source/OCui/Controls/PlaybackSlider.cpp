// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

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

    //ui->horizontalSlider->setValue(player->position());
}

void PlaybackSlider::SetupEvents()
{
    connect(ui->playButton, SIGNAL(toggled(bool)), SLOT(OnPlayButtonToggled(bool)));

    connect(ui->stopButton, SIGNAL(clicked()), SLOT(OnStopClicked()));

    connect(ui->prevFrameButton, SIGNAL(clicked()), this, SLOT(PrevFrame()));
    connect(ui->nextFrameButton, SIGNAL(clicked()), this, SLOT(NextFrame()));

    connect(ui->jumpStartButton, SIGNAL(clicked()), this, SLOT(OnJumpStartClicked()));
    connect(ui->jumpEndButton, SIGNAL(clicked()), this, SLOT(OnJumpEndClicked()));
}

void PlaybackSlider::SetupPlayer()
{
//    QtAV::setLogLevel(QtAV::LogWarning);

//    QVBoxLayout *vl = new QVBoxLayout(ui->frame);
//    vl->setMargin(0);
//    QtAV::Widgets::registerRenderers();
//    player = new QtAV::AVPlayer(vl);
//    QtAV::VideoOutput* videoOutput = new QtAV::VideoOutput(vl);
//    if (!videoOutput->widget())
//    {
//        return;
//    }

//    player->setRenderer(videoOutput);
//    QWidget* widget = videoOutput->widget();
//    vl->addWidget(widget);
//    //ui->frame->setLayout(vl);
//    QPoint pos = widget->pos();
//    int width = widget->width();
//    int height = widget->height();

//    //videoOutput->widget()->showFullScreen();

//    player->setSeekType(QtAV::AccurateSeek);

//    connect(player, &QtAV::AVPlayer::positionChanged, this, &PlaybackSlider::UpdateSlider);

//    connect(player, &QtAV::AVPlayer::started, [this](){
//        connect(player, &QtAV::AVPlayer::seekFinished, this, &PlaybackSlider::PauseAfterLoad);
//        player->setPosition(0);
//        ui->horizontalSlider->setRange(0, player->duration());
//    });

//    player->play();
}

void PlaybackSlider::PrevFrame()
{
    //player->stepBackward();
}

void PlaybackSlider::NextFrame()
{
    //player->stepForward();
}

void PlaybackSlider::PauseAfterLoad()
{
    //player->pause(true);
    //disconnect(player, &QtAV::AVPlayer::seekFinished, this, &PlaybackSlider::PauseAfterLoad);
}

PlaybackSlider::~PlaybackSlider()
{
    delete ui;
}

void PlaybackSlider::OnPlayButtonToggled(bool toggled)
{
    //player->togglePause();

    if(toggled)
    {
        ui->playRevButton->setChecked(false);
    }
}

void PlaybackSlider::OnStopClicked()
{
    ui->playButton->setChecked(false);
    ui->playRevButton->setChecked(false);

//    player->togglePause();
//    player->setState(QtAV::AVPlayer::PausedState);
//    player->setPosition(0);
}

void PlaybackSlider::OnJumpStartClicked()
{
    ui->playButton->setChecked(false);
    ui->playRevButton->setChecked(false);

//    player->togglePause();
//    player->setState(QtAV::AVPlayer::PausedState);
//    player->setPosition(0);
}

void PlaybackSlider::OnJumpEndClicked()
{
    ui->playButton->setChecked(false);
    ui->playRevButton->setChecked(false);

//    player->togglePause();
//    player->setState(QtAV::AVPlayer::PausedState);
//    player->setPosition(player->duration());
}

void PlaybackSlider::LoadFile(QString filePath)
{
//    player->setFile(filePath);
//    player->load();
//    player->play();
}
