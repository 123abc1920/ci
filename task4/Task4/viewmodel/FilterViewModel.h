#pragma once

#include "Query.h"
#include <vector>

class FilterViewModel
{
private:
    Query mainQuery;

public:
    FilterViewModel();

    void addToQuery(string subject, bool isExclude);
    void removeFromQuery(string subject, bool isExclude);
    string getQueryText();
    set<string> getQueryData(bool isExclude);
    vector<string> getSubjects();
    set<string> getIncludes();
    set<string> getExcludes();
};