#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <mutex>
#include <string>
#include <sstream>

#include "ILogger.h"
#include "OCCore_export.h"

namespace OC
{
	namespace Log
	{
		//References:
		//http://silviuardelean.ro/2012/06/05/few-singleton-approaches/
		//http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
		//Notice:
		//Decided against a base class for Singleton to prevent further usage
		//Logger should be the only one to use this "anti-pattern" for now
		//An injection approach should be used later
		class OCCORE_EXPORT Logger final
		{
		private:
			ILogger* _loggerImplementation;

			Logger();

		public:
			Logger(const Logger& rs) = delete;
			Logger& operator = (const Logger& rs) = delete;

			static Logger& GetInstance();

			~Logger();

			void LogWarning(std::string message, std::string file, unsigned int line);
			void LogError(std::string message, std::string file, unsigned int line);
			void LogInfo(std::string message, std::string file, unsigned int line);
			void LogFatal(std::string message, std::string file, unsigned int line);

		protected:
			enum Level {
				LevelNone = 0,

				LevelFatal,
				LevelError,
				LevelWarning,
				LevelInfo,

				FirstLevel = LevelFatal,
				LastLevel = LevelInfo,
				Levels = LastLevel - FirstLevel + 1
			};

			std::string FormatMessage(Level level, std::string message, std::string file, int lineNumber);
		};

#ifdef _DEBUG
#define OC_LOG_INFO(message) OC::Log::Logger::GetInstance().LogInfo(message, __FILE__, __LINE__)
#define OC_LOG_WARNING(message) OC::Log::Logger::GetInstance().LogWarning(message, __FILE__, __LINE__)
#define OC_LOG_ERROR(message) OC::Log::Logger::GetInstance().LogError(message, __FILE__, __LINE__)
#define OC_LOG_FATAL(message) OC::Log::Logger::GetInstance().LogFatal(message, __FILE__, __LINE__)
#else 
#define OC_LOG_INFO(message) void(0)
#define OC_LOG_WARNING(message) void(0)
#define OC_LOG_ERROR(message) void(0)
#define OC_LOG_FATAL(message) void(0)
#endif
	} // namespace Log
} // namespace OC

#endif //LOGGER_H
