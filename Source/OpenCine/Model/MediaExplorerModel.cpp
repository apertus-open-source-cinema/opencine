#include "MediaExplorerModel.h"

#include <QDir>

/*ClipInfo::ClipInfo(QObject *parent)
    : QObject(parent)
{
}*/

ClipInfo::ClipInfo(const QString &path, const unsigned int& width, const unsigned int& height, const unsigned int& fps, QObject *parent):
QObject(parent),
_path(path),
_width(width),
_height(height),
_fps(fps)
{
    _name = path;
}

QString ClipInfo::Name() const
{
    return _name;
}

unsigned int ClipInfo::Width() const
{
    return _width;
}

unsigned int ClipInfo::Height() const
{
    return _height;
}

unsigned int ClipInfo::FPS() const
{
    return _fps;
}

bool MediaExplorerModel::EnumerateAvailableData(std::string folderPath, ClipInfo** clipData)
{
  QDir dir(QString::fromStdString(folderPath));

  QStringList filters;
  filters << "*.dng";
  dir.setNameFilters(filters);

  dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

  if(dir.count() == 0)
  {
    return false;
  }

  //Get metadata for the first file, no error checks available atm
  std::string fileName = dir.entryList().at(0).toStdString();
  OCFrame* imageData = _dataProvider->GetMetadataFromFile(folderPath + "/" + fileName);

  if(imageData)
  {    
    *clipData = new ClipInfo(dir.dirName(), imageData->GetWidth(), imageData->GetHeight(), 0);

    delete imageData;
    return true;
  }

  //if(imageData != nullptr)
  //{
  //  emit NewDataAdded(imageData);
  //  return true;
  // }

  return false;
}

ClipInfo* MediaExplorerModel::GetClipByID(unsigned int clipID)
{
  if(clipID < _availableData.size())
  {
    return _availableData.at(clipID);
  }

  return nullptr;
}
