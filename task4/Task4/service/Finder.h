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

    bool notHasExcludes(const Student &s) const;
    bool hasIncludes(const Student &s) const;

public:
    explicit Finder(const Query &q, const InMemoryRepository &repo, Logger &logger);
    ~Finder() = default;

    std::vector<std::string> find() const;
};
