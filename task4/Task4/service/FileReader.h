#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Student.h"
#include "ILoggable.h"

using namespace std;

class FileReader : public ILoggable
{
private:
    map<string, vector<string>> parse(const string &data);

public:
    FileReader(Logger &logger);
    ~FileReader();

    map<int, Student> readDB(string data);
    map<int, string> readSubjects(string data);
};