#pragma once
#include "Logger.h"
#include <memory>

class BaseViewModel
{
private:
    std::shared_ptr<Logger> logger;

public:
    BaseViewModel(Logger &logger)
        : logger(std::shared_ptr<Logger>(
              std::shared_ptr<void>(),
              &logger))
    {
    }
    ~BaseViewModel() = default;

    void writeLog(const Logger::Level &level, const std::string &message)
    {
        logger->write(level, message);
    }
};