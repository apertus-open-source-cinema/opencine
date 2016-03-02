#ifndef LOG4CXXLOGGER_H
#define LOG4CXXLOGGER_H

#include "ILogger.h"

namespace OC {
namespace Log {

class OC_EXPORT log4cxxLogger : virtual public ILogger {
public:
    void LogWarning(std::string message);
    void LogError(std::string message);
    void LogInfo(std::string message);
    void LogFatal(std::string message);
};

} // namespace Log
} // namespace OC

#endif //LOG4CXXLOGGER_H
