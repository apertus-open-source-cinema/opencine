#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>

#include <vector>
#include <string>

class OCSession
{

};

class OCContext : public QObject
{
  Q_OBJECT

  OCSession* _session;

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

signals:
  void SessionChanged();
};

#endif //CONTEXT_H
