#ifndef LOG4CXXLOGGER_H
#define LOG4CXXLOGGER_H

#include "ILogger.h"

class log4cxxLogger : public ILogger
{
public:
    void LogWarning(std::string message);
    void LogError(std::string message);
    void LogInfo(std::string message);
    void LogFatal(std::string message);
};

#endif //LOG4CXXLOGGER_H
