#ifndef MEDIAEXPLORERMODEL_H
#define MEDIAEXPLORERMODEL_H

#include <QObject>
#include <string>
#include <vector>

#include "API/IDataProvider.h"

using namespace OpenCineAPI;

class ClipInfo
{
  std::string _name;
  unsigned int _width;
  unsigned int _height;
  std::string _path;

public:
  unsigned int GetWidth()
  {
    return _width;
  }

  unsigned int GetHeight()
  {
    return _height;
  }

  std::string GetPath()
  {
    return _path;
  }

  unsigned int SetSize(unsigned int width, unsigned int height)
  {
    _width = width;
    _height = height;
  }
};

class MediaExplorerModel : public QObject
{
  Q_OBJECT

  std::vector<ClipInfo*> _availableData;

  IDataProvider* _dataProvider;

public:

  MediaExplorerModel(IDataProvider* dataProvider)
  {
    _dataProvider = dataProvider;
  }

  //Currently single folder only, subfolders will be implemented later
  bool EnumerateAvailableData(std::string folderPath, ClipInfo& clipData);

  ClipInfo* GetClipByID(unsigned int clipID);

signals:
  void NewDataAdded(OCImage* metaData);
};

#endif //MEDIAEXPLORERMODEL_H
