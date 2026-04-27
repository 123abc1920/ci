#pragma once

#include <iostream>
#include <set>
#include <string>

using namespace std;

class Query
{
private:
    set<string> includes;
    set<string> excludes;

public:
    void addInclude(string subject);
    void addExclude(string subject);
    void deleteInclude(string subject);
    void deleteExclude(string subject);
};