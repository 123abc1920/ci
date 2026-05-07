#pragma once

#include "Query.h"
#include "InMemoryRepository.h"
#include <vector>
#include <string>
#include "Student.h"

class Saver
{
private:
    string convertToString(vector<string> data);

public:
    Saver();
    ~Saver();

    bool save(vector<string> data, string filePath);
};