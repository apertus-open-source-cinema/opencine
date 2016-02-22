#include "ILogger.h"

#include "EasyLoggingAdapter.h"
#include "log4cxxLogger.h"

Logger::Logger()
{
    //loggerImplementation = new log4cxxLogger();
    loggerImplementation = new EasyLoggingAdapter();
}

void Logger::LogWarning(std::string message)
{
    loggerImplementation->LogWarning(message);
}

void Logger::LogError(std::string message)
{
    loggerImplementation->LogError(message);
}

void Logger::LogInfo(std::string message)
{
    loggerImplementation->LogInfo(message);
}

void Logger::LogFatal(std::string message)
{
    loggerImplementation->LogFatal(message);
}
