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
    string convertToString(vector<string> data);

public:
    Saver(Logger &logger);
    ~Saver();

    bool save(vector<string> data, string filePath);
};