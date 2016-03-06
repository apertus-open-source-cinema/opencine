#include "EasyLoggingAdapter.h"

#define ELPP_NO_DEFAULT_LOG_FILE
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

using namespace OC::Log;

EasyLoggingAdapter::EasyLoggingAdapter()
{
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime %level %msg (%loc)");
    defaultConf.setGlobally(el::ConfigurationType::Filename, "Logs/OC.log");
    el::Loggers::reconfigureLogger("default", defaultConf);
}

void EasyLoggingAdapter::LogWarningImpl(std::string message)
{
    LOG(WARNING) << message;
}

void EasyLoggingAdapter::LogErrorImpl(std::string message)
{
    LOG(ERROR) << message;
}

void EasyLoggingAdapter::LogInfoImpl(std::string message)
{
    LOG(INFO) << message;
}

void EasyLoggingAdapter::LogFatalImpl(std::string message)
{
    LOG(FATAL) << message;
}
