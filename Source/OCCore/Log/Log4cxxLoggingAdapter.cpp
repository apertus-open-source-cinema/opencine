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

} // namespace Log
} // namespace OC 
