#pragma once
#include "Logger.h"
#include <memory>
#include <string>

class ILoggable
{
private:
    Logger *logger;

public:
    explicit ILoggable(Logger &logger);
    virtual ~ILoggable() = default;

    void writeLog(const Logger::Level &level, const std::string &message) const;
};
