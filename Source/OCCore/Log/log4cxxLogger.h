#ifndef LOG4CXXLOGGER_H
#define LOG4CXXLOGGER_H

#include "ILogger.h"

namespace OC
{
	namespace Log
	{
		class OCCORE_EXPORT log4cxxLogger : virtual public ILogger
		{
		public:
			virtual void LogWarning(std::string message);
			virtual void LogError(std::string message);
			virtual void LogInfo(std::string message);
			virtual void LogFatal(std::string message);
		};
    }
}

#endif //LOG4CXXLOGGER_H
