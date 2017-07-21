// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

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
