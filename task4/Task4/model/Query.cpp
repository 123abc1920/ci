#include "Query.h"

void Query::addInclude(const std::string &subject)
{
    includes.insert(subject);
    excludes.erase(subject);
}

void Query::addExclude(const std::string &subject)
{
    excludes.insert(subject);
    includes.erase(subject);
}

void Query::deleteInclude(const std::string &subject)
{
    includes.erase(subject);
}

void Query::deleteExclude(const std::string &subject)
{
    excludes.erase(subject);
}

std::string Query::getIncludes() const
{
    std::string result;
    for (const auto &subject : includes)
    {
        if (!result.empty())
            result += ", ";
        result += subject;
    }
    return result;
}

std::string Query::getExcludes() const
{
    std::string result;
    for (const auto &subject : excludes)
    {
        if (!result.empty())
            result += ", ";
        result += subject;
    }
    return result;
}

const std::set<std::string> &Query::getExcludesSet() const
{
    return excludes;
}

const std::set<std::string> &Query::getIncludesSet() const
{
    return includes;
}
