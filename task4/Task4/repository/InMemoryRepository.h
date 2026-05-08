#pragma once

#include <map>
#include <string>
#include "Student.h"

class InMemoryRepository
{
private:
    std::map<int, Student> inMemoryDB;

public:
    InMemoryRepository() = default;

    void setData(const std::map<int, Student> &data);
    const std::map<int, Student> &getAll() const;
};
