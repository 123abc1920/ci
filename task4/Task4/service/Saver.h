#pragma once

#include "Query.h"
#include "InMemoryRepository.h"
#include <vector>
#include <string>
#include "Student.h"
#include "ILoggable.h"
#include "Logger.h"

class Saver : public ILoggable
{
private:
    std::string convertToString(std::vector<std::string> data);

public:
    Saver(Logger &logger);
    ~Saver();

    bool save(std::vector<std::string> data, std::string filePath);
};