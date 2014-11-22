#ifndef MEDIAEXPLORERMODEL_H
#define MEDIAEXPLORERMODEL_H

#include <QObject>
#include <string>
#include <vector>

#include "API/IDataProvider.h"

using namespace OpenCineAPI;

class ClipData
{
  std::string _name;
  unsigned int _width;
  unsigned int _height;

public:
  unsigned int GetWidth()
  {
    return _width;
  }
};

class MediaExplorerModel : public QObject
{
  Q_OBJECT

  std::vector<ClipData> _availableData;

  IDataProvider* _dataProvider;

public:

  MediaExplorerModel(IDataProvider* dataProvider)
  {
    _dataProvider = dataProvider;
  }

  //Currently single folder only, subfolders will be implemented later
  bool EnumerateAvailableData(std::string folderPath);

signals:
  void NewDataAdded(OCImage* metaData);
};

#endif //MEDIAEXPLORERMODEL_H
