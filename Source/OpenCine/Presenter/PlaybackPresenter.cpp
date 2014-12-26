#include "PlaybackPresenter.h"

PlaybackPresenter::PlaybackPresenter(OCContext* context) :
_currentFrame(0)
{
  _context = context;

  connect(_context, SIGNAL(SessionChanged(OCSession*)), this, SLOT(OnSessionChanged(OCSession*)));

  _timer = new QTimer(this);
  connect(_timer, SIGNAL(timeout()), this, SLOT(Update()));
}

PlaybackPresenter::~PlaybackPresenter()
{
}


void PlaybackPresenter::SetFrame(unsigned int frame)
{

}

/*void PlaybackPresenter::UpdateViews()
{
  emit FrameChanged();
  if(currentFrame > _dataStorage->GetFrameCount() - 1)
  {
    currentFrame = 0;
  }

  OCImage* image = _dataStorage->GetFrame(currentFrame);
  emit NewDataAvailable(image);

  currentFrame++;
}*/

void PlaybackPresenter::OnSessionChanged(OCSession* session)
{
  _frameRate = 24;

  _session = session;

  emit SessionChanged(session);
}

void PlaybackPresenter::Update()
{
  OCFrame* frame = _session->GetDataStorage()->GetFrame(_currentFrame);
  emit FrameChanged(_currentFrame, frame);

  _currentFrame++;

  if(_currentFrame > _session->GetFrameCount())
  {
    _currentFrame = 0;
  }
}

/*std::vector<std::string> PlaybackPresenter::GetData()
{
    std::vector<std::string> data;

    data.push_back("Test 1");
    data.push_back("Test 2");
    data.push_back("Test 3");

    emit NewDataAvailable();

    return data;
}*/


void PlaybackPresenter::Play()
{
  int i = 0;

  _timer->start(1000.0 / _frameRate);

  //_timer.start();
}

void PlaybackPresenter::Pause()
{
}

void PlaybackPresenter::Stop()
{
  _timer->stop();
  _currentFrame = 0;
}

void PlaybackPresenter::NextFrame()
{
  _currentFrame++;
}

void PlaybackPresenter::PrevFrame()
{
  _currentFrame--;
}
