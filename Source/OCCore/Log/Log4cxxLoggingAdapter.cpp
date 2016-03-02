///////////////////////////////////////////////////////////////////////
///   File: Log4cxxLoggingAdapter.cpp
///   Date: 3/1/2016
///////////////////////////////////////////////////////////////////////
#include "Log4cxxLoggingAdapter.h"

namespace OC {
namespace Log {

Logger::Logger() {
    loggerImplementation = new log4cxxLogger();
}
Logger::~Logger() {
    if ((loggerImplementation)) {
        delete loggerImplementation;
    }
}

void Logger::LogWarning(std::string message) {
    if (loggerImplementation) loggerImplementation->LogWarning(message);
}
void Logger::LogError(std::string message) {
    if (loggerImplementation) loggerImplementation->LogError(message);
}
void Logger::LogInfo(std::string message) {
    if (loggerImplementation) loggerImplementation->LogInfo(message);
}
void Logger::LogFatal(std::string message) {
    if (loggerImplementation) loggerImplementation->LogFatal(message);
}

} // namespace Log
} // namespace OC 
