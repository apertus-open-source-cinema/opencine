#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>

#include <vector>
#include <string>

#include "API/IDataProvider.h"

using namespace OpenCineAPI;

class OCSession
{

};

class OCContext : public QObject
{
  Q_OBJECT

  OCSession* _session;

  IDataProvider* _dataProvider;

  std::vector<std::string> _availableData;

public:
  OCContext();

  OCSession* GetSession()
  {
    return _session;
  }

  void CreateSession()
  {
    emit SessionChanged();
  }

  IDataProvider* GetDefaultDataProvider()
  {
    return _dataProvider;
  }

signals:
  void SessionChanged();
};

#endif //CONTEXT_H
