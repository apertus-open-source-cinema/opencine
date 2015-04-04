#include "MediaExplorerPresenter.h"

#include <QTimer>
#include <QFileDialog>

//#include "../DataStorage/StaticMemoryAllocator.h"

MediaExplorerPresenter::MediaExplorerPresenter(OCContext* context)
{
  _context = context;
  _model = new MediaExplorerModel(_context->GetDefaultDataProvider());
}

MediaExplorerPresenter::~MediaExplorerPresenter()
{
}

void MediaExplorerPresenter::LoadClip(unsigned int clipNumber)
{
  ClipItem* clipData = _model->GetClipByID(clipNumber);
  
  _context->CreateSession(clipData->Path());
}

void MediaExplorerPresenter::ImportFolder()
{
  QString dir = QFileDialog::getExistingDirectory(0, tr("_Choose directory to import from ..."), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  ClipItem* clipData = nullptr;

  if(_model->EnumerateAvailableData(dir.toStdString(), &clipData))
  {
    emit NewDataFound(clipData);
  }
}
