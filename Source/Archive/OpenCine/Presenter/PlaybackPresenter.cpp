#include "PlaybackPresenter.h"

PlaybackPresenter::PlaybackPresenter(OCContext* context) :
    _currentFrame(0),
    _context(context)
{
    connect(_context, SIGNAL(SessionChanged(OCSession*)), SLOT(OnSessionChanged(OCSession*)));

    _timer = new QTimer(this);
    //connect(_timer, SIGNAL(timeout()), SLOT(Update()));
}

PlaybackPresenter::~PlaybackPresenter()
{
}

void PlaybackPresenter::SetFrame(unsigned int frameNumber)
{
    _currentFrame = frameNumber;

    Update();
}

void PlaybackPresenter::OnSessionChanged(OCSession* session)
{
    _frameRate = 24;

    _session = session;

    Update();

    emit SessionChanged(session);
}

void PlaybackPresenter::Update()
{
    OCFrame* frame = _session->GetDataStorage()->GetFrame(_currentFrame);
    emit FrameChanged(_currentFrame, frame);
}

void PlaybackPresenter::Play()
{
    connect(_timer, SIGNAL(timeout()), SLOT(PlayHandler()));
    _timer->start(1000.0 / _frameRate);
}

void PlaybackPresenter::PlayHandler()
{
    _currentFrame++;

    if(_currentFrame > _session->GetFrameCount())
    {
        _currentFrame = 0;
    }

    Update();
}

void PlaybackPresenter::PlayRev()
{
    connect(_timer, SIGNAL(timeout()), SLOT(PlayRevHandler()));
    _timer->start(1000.0 / _frameRate);
}

void PlaybackPresenter::PlayRevHandler()
{
    _currentFrame--;

    if(_currentFrame < 0)
    {
        _currentFrame = _session->GetFrameCount();
    }

    Update();
}

void PlaybackPresenter::Pause()
{
    disconnect(_timer, SIGNAL(timeout()), this, SLOT(PlayRevHandler()));
    disconnect(_timer, SIGNAL(timeout()), this, SLOT(PlayHandler()));

    _timer->stop();
}

void PlaybackPresenter::Stop()
{
    _timer->stop();
    _currentFrame = 0;

    Update();
}

void PlaybackPresenter::NextFrame()
{
    _currentFrame++;

    if(_currentFrame > _session->GetFrameCount())
    {
        _currentFrame = _session->GetFrameCount();
    }

    Update();
}

void PlaybackPresenter::PrevFrame()
{
    _currentFrame--;

    if(_currentFrame < 0)
    {
        _currentFrame = 0;
    }

    Update();
}

void PlaybackPresenter::JumpToStart()
{
    _currentFrame = 0;

    Update();
}

void PlaybackPresenter::JumpToEnd()
{
    _currentFrame = _session->GetFrameCount();

    Update();
}
