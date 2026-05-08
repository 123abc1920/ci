#pragma once
#include <string>
#include <fstream>
#include <string_view>

class Logger
{
public:
    enum class Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    explicit Logger(const std::string &filename = "logs.txt");

    void write(Level level, std::string_view message);

private:
    std::ofstream logFile;
    std::string_view levelToString(Level level);
};
