#pragma once

#include "Query.h"
#include <vector>
#include "SubjectsRepository.h"

class FilterViewModel
{
private:
    Query mainQuery;
    SubjectsRepository subjectsRepository;

public:
    FilterViewModel(const SubjectsRepository &subjectsRepository);

    void addToQuery(string subject, bool isExclude);
    void removeFromQuery(string subject, bool isExclude);
    string getQueryText();
    set<string> getQueryData(bool isExclude);
    vector<string> getSubjects();
    set<string> getIncludes();
    set<string> getExcludes();
};