#ifndef EASYLOGGINGADAPTER_H
#define EASYLOGGINGADAPTER_H

#include "ILogger.h"

namespace OC
{
    namespace Log
    {
        class EasyLoggingAdapter : public ILogger
        {
        public:
            EasyLoggingAdapter();

            void LogWarningImpl(std::string message);
            void LogErrorImpl(std::string message);
            void LogInfoImpl(std::string message);
            void LogFatalImpl(std::string message);
        };
    }
}

#endif //EASYLOGGINGADAPTER_H
