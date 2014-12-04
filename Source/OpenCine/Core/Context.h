               #ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>

#include <vector>
#include <string>
#include <memory>

#include "API/IDataProvider.h"

using namespace OpenCineAPI;

class OCSession
{
  unsigned int _width;
  unsigned int _height;

  std::string _name;

  std::shared_ptr<IDataStorage> _dataStorage;

public:
  IDataStorage* GetDataStorage()
  {
    return _dataStorage.get();
  }
};

class OCContext : public QObject
{
  Q_OBJECT

  std::unique_ptr<OCSession> _session;

  IDataProvider* _dataProvider;

  std::vector<std::string> _availableData;

public:
  OCContext();

  OCSession* GetSession()
  {
    return _session.get();
  }

  void CreateSession()
  {
    _session = std::unique_ptr<OCSession>(new OCSession());
    emit SessionChanged();
  }

  IDataProvider* GetDefaultDataProvider()
  {
    return _dataProvider;
  }

  void LoadClip();

signals:
  void SessionChanged();
};

#endif //CONTEXT_H
