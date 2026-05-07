#include "Logger.h"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>

Logger::Logger() {}

const std::string LOG_FILE_PATH = "logs.txt";

string levelToString(Logger::Level level)
{
    switch (level)
    {
    case Logger::Level::DEBUG:
        return "DEBUG";
    case Logger::Level::INFO:
        return "INFO";
    case Logger::Level::WARNING:
        return "WARNING";
    case Logger::Level::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

void Logger::write(const Level &level, const string &message)
{
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    ofstream logFile(LOG_FILE_PATH, ios::app);

    if (logFile.is_open())
    {
        logFile << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
        logFile << " | " << setw(7) << levelToString(level) << " | " << message << endl;
        logFile.close();
    }
}

Logger::~Logger() {}