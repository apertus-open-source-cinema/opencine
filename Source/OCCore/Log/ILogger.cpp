#include "ILogger.h"
#include <sstream>
#include <string>

#include "EasyLoggingAdapter.h"
#include "log4cxxLogger.h"

using namespace OC::Log;

Logger::Logger()
{
    //loggerImplementation = new log4cxxLogger();
    loggerImplementation = new EasyLoggingAdapter();
}

Logger::~Logger()
{
    if (loggerImplementation != nullptr)
    {
        delete loggerImplementation;
    }
}

void Logger::LogWarning(std::string message)
{
    if (loggerImplementation != nullptr)
    {
        loggerImplementation->LogWarning(message);
    }
}

void Logger::LogError(std::string message)
{
    if (loggerImplementation != nullptr)
    {
        loggerImplementation->LogError(message);
    }
}

void Logger::LogInfo(std::string message)
{
    if (loggerImplementation != nullptr)
    {
        loggerImplementation->LogInfo(message);
    }
}

void Logger::LogFatal(std::string message)
{
    if (loggerImplementation != nullptr)
    {
        loggerImplementation->LogFatal(message);
    }
}

std::string Logger::FormatMessage(Level level, std::string message, std::string file, int lineNumber)
{
    return message + " (" + file + ":" + std::to_string(lineNumber) + ")";
}
