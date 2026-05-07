#pragma once

#include <iostream>
#include <string>

using namespace std;

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

    Logger();
    ~Logger();

    void write(const Level &level, const string &message);
};