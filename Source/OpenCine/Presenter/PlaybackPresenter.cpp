#include "PlaybackPresenter.h"

PlaybackPresenter::PlaybackPresenter(OCContext* context)
{
  _context = context;

  connect(_context, SIGNAL(SessionChanged()), this, SLOT(OnSessionChanged()));
}

PlaybackPresenter::~PlaybackPresenter()
{
}

void PlaybackPresenter::UpdateViews()
{
    /*if(currentFrame > _dataStorage->GetFrameCount() - 1)
    {
        currentFrame = 0;
    }

    OCImage* image = _dataStorage->GetFrame(currentFrame);
    emit NewDataAvailable(image);

    currentFrame++;*/
}

void PlaybackPresenter::OnSessionChanged()
{
  int i = 0;
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
