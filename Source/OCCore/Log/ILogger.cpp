#include "ILogger.h"
#include <sstream>
#include <string>

namespace OC {
namespace Log {

std::string Logger::FormatMessage
(std::string message, std::string file, int lineNumber) {
    return message + " (" + file + ":" + std::to_string(lineNumber) + ")";
}

} // namespace Log
} // namespace OC
