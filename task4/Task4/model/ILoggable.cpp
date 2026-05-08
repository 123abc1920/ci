#include "ILoggable.h"

ILoggable::ILoggable(Logger &logger)
    : logger(std::shared_ptr<Logger>(std::shared_ptr<void>(), &logger))
{
}

void ILoggable::writeLog(const Logger::Level &level, const std::string &message)
{
    if (this->logger)
    {
        this->logger->write(level, message);
    }
}
