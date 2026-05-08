#pragma once

#include <map>
#include <vector>
#include <string>
#include <string_view>
#include "Student.h"
#include "ILoggable.h"

class FileReader : public ILoggable
{
private:
    std::map<std::string, std::vector<std::string>> parse(std::string_view data);

public:
    explicit FileReader(Logger &logger);
    ~FileReader() = default;

    std::map<int, Student> readDB(std::string_view data);
    std::map<int, std::string> readSubjects(std::string_view data);
};
