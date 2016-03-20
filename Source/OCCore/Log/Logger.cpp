#include "Logger.h"

#include <sstream>
#include <string>

#include "EasyLoggingAdapter.h"
#include "log4cxxLogger.h"

using namespace OC::Log;

Logger::Logger()
{
    //loggerImplementation = new log4cxxLogger();
    _loggerImplementation = new EasyLoggingAdapter();
}

Logger &Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

Logger::~Logger()
{
    if (_loggerImplementation != nullptr)
    {
        delete _loggerImplementation;
    }
}

void Logger::LogError(std::string message, std::string file, unsigned int line)
{
    if (_loggerImplementation != nullptr)
    {
        _loggerImplementation->LogError(message, file, line);
    }
}

void Logger::LogWarning(std::string message, std::string file, unsigned int line)
{
    if (_loggerImplementation != nullptr)
    {
        _loggerImplementation->LogWarning(message, file, line);
    }
}

void Logger::LogInfo(std::string message, std::string file, unsigned int line)
{
    if (_loggerImplementation != nullptr)
    {
        _loggerImplementation->LogInfo(message, file, line);
    }
}

void Logger::LogFatal(std::string message, std::string file, unsigned int line)
{
    if (_loggerImplementation != nullptr)
    {
        _loggerImplementation->LogFatal(message, file, line);
    }
}

std::string Logger::FormatMessage(Level level, std::string message, std::string file, int lineNumber)
{
    return message + " (" + file + ":" + std::to_string(lineNumber) + ")";
}
