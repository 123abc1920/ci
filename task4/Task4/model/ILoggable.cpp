#include "ILoggable.h"

ILoggable::ILoggable(Logger &logger) : logger(&logger) {}

void ILoggable::writeLog(const Logger::Level &level, const std::string &message) const
{
    if (logger)
    {
        logger->write(level, message);
    }
}
