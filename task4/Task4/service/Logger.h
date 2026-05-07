#pragma once

#include <iostream>
#include <string>

using namespace std;

class Logger
{
public:
    Logger();
    ~Logger();

    void write(const std::string &level, const std::string &message);
};