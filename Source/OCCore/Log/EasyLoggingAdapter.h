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

            void LogWarning(std::string message, std::string file, unsigned int line);
            void LogError(std::string message, std::string file, unsigned int line);
            void LogInfo(std::string message, std::string file, unsigned int line);
            void LogFatal(std::string message, std::string file, unsigned int line);
        };
    }
}

#endif //EASYLOGGINGADAPTER_H
