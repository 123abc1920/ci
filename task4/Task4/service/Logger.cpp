#include "Logger.h"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>

Logger::Logger() {}

const std::string LOG_FILE_PATH = "app_log.txt";

void Logger::write(const std::string &level, const std::string &message)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::ofstream logFile(LOG_FILE_PATH, std::ios::app);

    if (logFile.is_open())
    {
        logFile << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << " | "
                << std::setw(7) << level << " | "
                << message << std::endl;

        logFile.close();
    }
}

Logger::~Logger() {}