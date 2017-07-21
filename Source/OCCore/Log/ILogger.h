// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef ILOGGER_H
#define ILOGGER_H

#include <memory>
#include <mutex>
#include <string>
#include <sstream>

#include "OCCore_export.h"

namespace OC
{
	namespace Log
	{
		class OCCORE_EXPORT ILogger {
		public:
			virtual ~ILogger() {}

			virtual void LogWarning(std::string message, std::string file, unsigned int line) = 0;
			virtual void LogError(std::string message, std::string file, unsigned int line) = 0;
			virtual void LogInfo(std::string message, std::string file, unsigned int line) = 0;
			virtual void LogFatal(std::string message, std::string file, unsigned int line) = 0;
		};
    }
}

#endif //ILOGGER_H
