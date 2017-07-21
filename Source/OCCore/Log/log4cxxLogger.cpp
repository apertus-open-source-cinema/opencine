// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "log4cxxLogger.h"

#include <iostream>

namespace OC
{
	namespace Log
	{
		void log4cxxLogger::LogWarning(std::string message)
		{
			std::cout << "WARNING: " << message << std::endl;
		}

		void log4cxxLogger::LogError(std::string message)
		{
			std::cout << "ERROR: " << message << std::endl;
		}

		void log4cxxLogger::LogInfo(std::string message)
		{
			std::cout << "INFO: " << message << std::endl;
		}

		void log4cxxLogger::LogFatal(std::string message)
		{
			std::cout << "FATAL: " << message << std::endl;
		}
    }
}
