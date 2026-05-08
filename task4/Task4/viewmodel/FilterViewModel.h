#pragma once

#include "Query.h"
#include <vector>
#include <string>
#include <set>
#include <string_view>
#include "SubjectsRepository.h"
#include "InMemoryRepository.h"
#include "ILoggable.h"

class FilterViewModel : public ILoggable
{
private:
    Query query;
    SubjectsRepository subjectsRepo;
    InMemoryRepository repository;

public:
    FilterViewModel(const SubjectsRepository &subjectsRepo,
                    const InMemoryRepository &repo,
                    Logger &logger);

    void addToQuery(const std::string &subject, bool isExclude);
    void removeFromQuery(const std::string &subject, bool isExclude);

    std::string getQueryText() const;

    const std::set<std::string> &getQueryData(bool isExclude) const;
    std::vector<std::string> getSubjects() const;

    const std::set<std::string> &getIncludes() const;
    const std::set<std::string> &getExcludes() const;

    const SubjectsRepository &getSubjectsRepository() const { return subjectsRepo; }
    const InMemoryRepository &getInMemoryRepository() const { return repository; }
    const Query &getQuery() const { return query; }
};
