#include "Logger.h"
#include <iomanip>
#include <chrono>

Logger::Logger(const std::string &filename)
{
    logFile.open(filename, std::ios::app);
}

std::string_view Logger::levelToString(Level level)
{
    switch (level)
    {
    case Level::DEBUG:
        return "DEBUG";
    case Level::INFO:
        return "INFO";
    case Level::WARNING:
        return "WARNING";
    case Level::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

void Logger::write(Level level, std::string_view message)
{
    if (!logFile.is_open())
        return;

    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    logFile << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S")
            << " | " << std::setw(7) << levelToString(level)
            << " | " << message << std::endl;
}
