#include "ILogger.h"
#include <sstream>
#include <string>

using namespace OC::Log;

void Logger::LogWarning(std::string message)
{
    if (loggerImplementation)
    {
        loggerImplementation->LogWarning(message);
    }
}

void Logger::LogError(std::string message)
{
    if (loggerImplementation)
    {
        loggerImplementation->LogError(message);
    }
}

void Logger::LogInfo(std::string message)
{
    if (loggerImplementation)
    {
        loggerImplementation->LogInfo(message);
    }
}
void Logger::LogFatal(std::string message) {
    if (loggerImplementation)
    {
        loggerImplementation->LogFatal(message);
    }
}

std::string Logger::FormatMessage(Level level, std::string message, std::string file, int lineNumber)
{
    return message + " (" + file + ":" + std::to_string(lineNumber) + ")";
}
