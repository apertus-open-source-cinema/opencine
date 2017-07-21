// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

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
