#pragma once

#include <vector>
#include <string>
#include <string_view>
#include "ILoggable.h"
#include "Logger.h"

class Saver : public ILoggable
{
private:
    std::string convertToString(const std::vector<std::string> &data) const;

public:
    explicit Saver(Logger &logger);
    ~Saver() = default;

    bool save(const std::vector<std::string> &data, std::string_view filePath) const;
};
