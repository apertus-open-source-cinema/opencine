#ifndef EASYLOGGINGADAPTER_H
#define EASYLOGGINGADAPTER_H

#include "ILogger.h"

class EasyLoggingAdapter : public ILogger
{
public:
    EasyLoggingAdapter();

    void LogWarning(std::string message);
    void LogError(std::string message);
    void LogInfo(std::string message);
    void LogFatal(std::string message);
};

#endif //EASYLOGGINGADAPTER_H
