#include "EasyLoggingAdapter.h"

#define ELPP_NO_DEFAULT_LOG_FILE
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

EasyLoggingAdapter::EasyLoggingAdapter()
{
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime %level %msg");
    defaultConf.setGlobally(el::ConfigurationType::Filename, "Logs/OC.log");
    el::Loggers::reconfigureLogger("default", defaultConf);
}

void EasyLoggingAdapter::LogWarning(std::string message)
{
    LOG(WARNING) << message;
}

void EasyLoggingAdapter::LogError(std::string message)
{
    LOG(ERROR) << message;
}

void EasyLoggingAdapter::LogInfo(std::string message)
{
    LOG(INFO) << message;
}

void EasyLoggingAdapter::LogFatal(std::string message)
{
    LOG(FATAL) << message;
}
