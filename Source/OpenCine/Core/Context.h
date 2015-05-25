#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QDir>

#include <vector>
#include <string>
#include <memory>

#include "API/IDataProvider.h"
#include "DataStorage/StaticMemoryAllocator.h"
#include "DataProvider/LibRawDataProvider.h"
#include "Log/ILogger.h"

#include "DataProvider/IDataFilter.h"

using namespace OpenCineAPI;

class OCSession
{
  unsigned int _width;
  unsigned int _height;

  std::string _name;

  std::shared_ptr<IDataStorage> _dataStorage;

public:
  OCSession()
  {
      _dataStorage = std::shared_ptr<IDataStorage>(new StaticMemoryAllocator());
  }

  IDataStorage* GetDataStorage()
  {
    return _dataStorage.get();
  }

  unsigned int GetFrameCount()
  {
    return _dataStorage.get()->GetFrameCount();
  }
};

class OCContext : public QObject
{
  Q_OBJECT

  std::shared_ptr<OCSession> _session;

  DataProviderFactory* _factory;
  IDataProvider* _dataProvider;

  std::shared_ptr<ILogger> _logger;

  std::vector<std::string> _availableData;

public:
  OCContext();

  ~OCContext();

  OCSession* GetSession()
  {
    return _session.get();
  }

  void CreateSession(QString path)
  {
    _session = std::unique_ptr<OCSession>(new OCSession());

    IDataStorage* dataStorage = _session->GetDataStorage();

    LibRawDataProvider* dataProvider = new LibRawDataProvider();

    std::shared_ptr<IDataFilter> filter = std::make_shared<DNGFilter>();
    QDir dir(path);

    QStringList filters;
    filters << "*.dng";
    dir.setNameFilters(filters);

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    for(unsigned int fileIndex = 0; fileIndex < dir.entryList().size(); fileIndex++)
    {
      QString tempPath = path + "/" + dir.entryList().at(fileIndex);
      dataProvider->LoadFile(dataStorage, tempPath.toStdString());
    }

    emit SessionChanged(_session.get());
  }

  /*IDataProvider* GetDefaultDataProvider()
  {
    return _dataProvider;
  }*/

  ILogger* GetLogger()
  {
      return _logger.get();
  }

  void LoadClip();

signals:
  void SessionChanged(OCSession* session);
};

#endif //CONTEXT_H
