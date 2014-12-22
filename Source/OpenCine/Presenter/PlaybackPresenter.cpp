#include "PlaybackPresenter.h"

PlaybackPresenter::PlaybackPresenter(OCContext* context)
{
  _context = context;

  connect(_context, SIGNAL(SessionChanged()), this, SLOT(OnSessionChanged()));
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
    emit SessionChanged(session);
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
  //_timer.start();
}

void PlaybackPresenter::Pause()
{
  //_timer.stop();
}

void PlaybackPresenter::Stop()
{
  //_timer.stop();
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
