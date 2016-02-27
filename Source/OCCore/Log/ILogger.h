#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

#include "OCCore_export.h"

class ILogger
{
public:
    virtual void LogWarning(std::string message) = 0;
    virtual void LogError(std::string message) = 0;
    virtual void LogInfo(std::string message) = 0;
    virtual void LogFatal(std::string message) = 0;
};

class OCCORE_EXPORT  Logger : public ILogger
{
    ILogger* loggerImplementation;

public:
    Logger();

    void LogWarning(std::string message);
    void LogError(std::string message);
    void LogInfo(std::string message);
    void LogFatal(std::string message);
};

#endif //ILOGGER_H
