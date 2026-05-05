#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Student.h"

using namespace std;

class FileReader
{
private:
    map<string, vector<string>> parse(const string &data);

public:
    map<int, Student> readDB(string data);
    map<int, string> readSubjects(string data);
};