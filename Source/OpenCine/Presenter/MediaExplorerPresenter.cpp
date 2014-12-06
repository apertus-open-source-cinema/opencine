#include "MediaExplorerPresenter.h"

#include <QTimer>
#include <QFileDialog>

//#include "../DataStorage/StaticMemoryAllocator.h"

MediaExplorerPresenter::MediaExplorerPresenter(OCContext* context)
{
  _context = context;
  _model = new MediaExplorerModel(_context->GetDefaultDataProvider());
  //_dataStorage = new StaticMemoryAllocator();

  //connect(this, NewDataAvailable())
}

MediaExplorerPresenter::~MediaExplorerPresenter()
{
}

void MediaExplorerPresenter::LoadClip(int clipNumber)
{
  _model->GetClipByID(clipNumber);
  
  _context->CreateSession();
}

void MediaExplorerPresenter::ImportFolder()
{
  _context->LoadClip();

  QString dir = QFileDialog::getExistingDirectory(0, tr("_Choose directory to import from ..."), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  ClipInfo* clipData = new ClipInfo();

  if(_model->EnumerateAvailableData(dir.toStdString(), *clipData))
  {
    emit NewDataFound(clipData);
  }

  //if(_dataStorage->ImportFolder(dir.toStdString()))
  //{

  //}

  // Start playBack
  //QTimer *timer = new QTimer(this);
  //connect(timer, SIGNAL(timeout()), this, SLOT(UpdateViews()));
  //timer->start(1000.0 / 24.0);
}

int currentFrame = 0;

/*void MediaExplorerPresenter::UpdateViews()
{
  if(currentFrame > _dataStorage->GetFrameCount() - 1)
  {
    currentFrame = 0;
  }

  OCImage* image = _dataStorage->GetFrame(currentFrame);
  emit NewDataAvailable(image);

  currentFrame++;
}*/



/*std::vector<std::string> MediaExplorerPresenter::GetData()
{
    std::vector<std::string> data;

    data.push_back("Test 1");
    data.push_back("Test 2");
    data.push_back("Test 3");

    emit NewDataAvailable();

    return data;
}*/
