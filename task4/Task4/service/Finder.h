#pragma once

#include "Query.h"
#include "InMemoryRepository.h"
#include <vector>
#include <string>
#include "Student.h"

class Finder
{
private:
    Query query;
    InMemoryRepository repository;

    bool notHasExcludes(Student& s);
    bool hasIncludes(Student& s);

public:
    Finder(Query &query, InMemoryRepository &inMemoryRepository);

    vector<string> find();
};