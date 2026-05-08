#pragma once

#include <set>
#include <string>

class Query
{
private:
    std::set<std::string> includes;
    std::set<std::string> excludes;

public:
    void addInclude(const std::string &subject);
    void addExclude(const std::string &subject);

    void deleteInclude(const std::string &subject);
    void deleteExclude(const std::string &subject);

    std::string getIncludes() const;
    std::string getExcludes() const;

    const std::set<std::string> &getIncludesSet() const;
    const std::set<std::string> &getExcludesSet() const;
};
