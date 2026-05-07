#pragma once

#include "Query.h"
#include <vector>
#include "SubjectsRepository.h"
#include "InMemoryRepository.h"

class FilterViewModel
{
private:
    Query mainQuery;
    SubjectsRepository subjectsRepository;
    InMemoryRepository repository;

public:
    FilterViewModel(SubjectsRepository &subjectsRepository, InMemoryRepository &repository);

    void addToQuery(string subject, bool isExclude);
    void removeFromQuery(string subject, bool isExclude);
    string getQueryText();
    set<string> getQueryData(bool isExclude);
    vector<string> getSubjects();
    set<string> getIncludes();
    set<string> getExcludes();

    SubjectsRepository getSubjectsRepository();
    InMemoryRepository getInMemoryRepository();
    Query getQuery();
};