#pragma once

#include <string>
#include <map>
#include <vector>

class SubjectsRepository
{
private:
    std::map<int, std::string> database;

public:
    SubjectsRepository() = default;

    void setData(const std::map<int, std::string> &data);

    std::vector<std::string> getAll() const;

    bool empty() const { return database.empty(); }
};
