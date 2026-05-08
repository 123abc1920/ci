#pragma once

#include "Query.h"
#include "InMemoryRepository.h"
#include <vector>
#include <string>
#include "Student.h"
#include "ILoggable.h"

class Finder : public ILoggable
{
private:
    Query query;
    InMemoryRepository repository;

    bool notHasExcludes(Student &s);
    bool hasIncludes(Student &s);

public:
    Finder(const Query &query, const InMemoryRepository &inMemoryRepository, Logger &logger);
    ~Finder();

    vector<string> find();
};