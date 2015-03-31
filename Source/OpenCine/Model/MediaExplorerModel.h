#ifndef MEDIAEXPLORERMODEL_H
#define MEDIAEXPLORERMODEL_H

#include <QObject>
#include <string>
#include <vector>

#include "API/IDataProvider.h"

using namespace OpenCineAPI;

class ClipInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString clipName READ Name CONSTANT)
    Q_PROPERTY(unsigned int clipWidth READ Width CONSTANT)
    Q_PROPERTY(unsigned int clipHeight READ Height CONSTANT)
    Q_PROPERTY(unsigned int clipFPS READ FPS CONSTANT)

public:
    ClipInfo(const QString &path, const QString &name, const unsigned int& width, const unsigned int& height, const unsigned int& fps, QObject* parent = 0);

    QString Path() const;
    QString Name() const;
    unsigned int Width() const;
    unsigned int Height() const;
    unsigned int FPS() const;

private:
    QString _name;
    QString _path;
    unsigned int _width;
    unsigned int _height;
    unsigned int _fps;
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
  bool EnumerateAvailableData(std::string folderPath, ClipInfo** clipData);

  ClipInfo* GetClipByID(unsigned int clipID);

signals:
  void NewDataAdded(OCFrame* metaData);
};

#endif //MEDIAEXPLORERMODEL_H
