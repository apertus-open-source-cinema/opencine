#ifndef ILOGGER_H
#define ILOGGER_H

#include "../OCCore.h"
#include <sstream>
#include <string>

#define OC_LOG_INFO(message) this->LogInfo(this->FormatMessage(this->LevelInfo, message, __FILE__, __LINE__))
#define OC_LOG_WARNING(message) this->LogWarning(this->FormatMessage(this->LevelWarning, message, __FILE__, __LINE__))
#define OC_LOG_ERROR(message) this->LogError(this->FormatMessage(this->LevelError, message, __FILE__, __LINE__))
#define OC_LOG_FATAL(message) this->LogFatal(this->FormatMessage(this->LevelFatal, message, __FILE__, __LINE__))

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
    enum Level {
        LevelNone = 0,

        LevelFatal,
        LevelError,
        LevelWarning,
        LevelInfo,

        FirstLevel = LevelFatal,
        LastLevel =  LevelInfo,
        Levels = LastLevel - FirstLevel + 1
    };
    std::string FormatMessage
    (Level level, std::string message, std::string file, int lineNumber);
};

} // namespace Log
} // namespace OC

#endif //ILOGGER_H
