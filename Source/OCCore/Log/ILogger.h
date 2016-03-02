#ifndef ILOGGER_H
#define ILOGGER_H

#include "../OCCore.h"
#include <sstream>
#include <string>

#define OC_LOG_WARNING(message) LogWarning(FormatMessage(message, __FILE__, __LINE__))
#define OC_LOG_ERROR(message) LogError(FormatMessage(message, __FILE__, __LINE__))
#define OC_LOG_INFO(message) LogInfo(FormatMessage(message, __FILE__, __LINE__))
#define OC_LOG_FATAL(message) LogFatal(FormatMessage(message, __FILE__, __LINE__))

namespace OC {
namespace Log {

class OCCORE_EXPORT ILogger {
public:
    virtual void LogWarning(std::string message) = 0;
    virtual void LogError(std::string message) = 0;
    virtual void LogInfo(std::string message) = 0;
    virtual void LogFatal(std::string message) = 0;
};

class OCCORE_EXPORT Logger : virtual public ILogger {
protected:
    ILogger* loggerImplementation;

public:
    Logger();
    virtual ~Logger();

    virtual void LogWarning(std::string message);
    virtual void LogError(std::string message);
    virtual void LogInfo(std::string message);
    virtual void LogFatal(std::string message);

protected:
    std::string FormatMessage
    (std::string message, std::string file, int lineNumber);
};

} // namespace Log
} // namespace OC

#endif //ILOGGER_H
