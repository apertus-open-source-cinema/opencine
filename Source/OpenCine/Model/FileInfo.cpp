#include "FileInfo.h"

#include <QDir>

FileInfo::FileInfo(const QString &path, const QString &name, const unsigned int& width, const unsigned int& height, const unsigned int& fps, QObject *parent):
QObject(parent),
_path(path),
_name(name),
_width(width),
_height(height),
_fps(fps)
{
    //_name = path;
}

QString FileInfo::Path() const
{
    return _path;
}

QString FileInfo::Name() const
{
    return _name;
}

unsigned int FileInfo::Width() const
{
    return _width;
}

unsigned int FileInfo::Height() const
{
    return _height;
}

unsigned int FileInfo::FPS() const
{
    return _fps;
}

/*bool FileInfo::EnumerateAvailableData(std::string folderPath, FileInfo** clipData)
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
    *clipData = new FileInfo(QString::fromStdString(folderPath), dir.dirName(), imageData->GetWidth(), imageData->GetHeight(), 0);
      _availableData.push_back(*clipData);

    delete imageData;
    return true;
  }

  return false;
}

FileInfo* FileInfo::GetClipByID(unsigned int clipID)
{
  if(clipID < _availableData.size())
  {
    return _availableData.at(clipID);
  }

  return nullptr;
}
*/
