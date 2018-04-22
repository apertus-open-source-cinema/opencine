#ifndef ILOGGER_H
#define ILOGGER_H

enum class LogType
{
  Info,
  Warning,
  Error,
  Critical
};

class ILogger
{
public:
  virtual ~ILogger() {}

  virtual void Log(LogType type, std::string message) = 0;
};

#endif //ILOGGER_H
