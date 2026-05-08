#pragma once
#include "Logger.h"
#include <memory>
#include <string>

class ILoggable
{
private:
    std::shared_ptr<Logger> logger;

public:
    ILoggable(Logger &logger);
    void writeLog(const Logger::Level &level, const std::string &message);
};
