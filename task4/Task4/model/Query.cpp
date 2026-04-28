#include "Query.h"

void Query::addInclude(string subject)
{
    if (includes.count(subject) <= 0)
    {
        includes.insert(subject);
    }
    if (excludes.count(subject) > 0)
    {
        deleteExclude(subject);
    }
}

void Query::addExclude(string subject)
{
    if (excludes.count(subject) <= 0)
    {
        excludes.insert(subject);
    }
    if (includes.count(subject) > 0)
    {
        deleteInclude(subject);
    }
}

void Query::deleteInclude(string subject)
{
    while (includes.count(subject) > 0)
    {
        includes.erase(subject);
    }
}

void Query::deleteExclude(string subject)
{
    while (excludes.count(subject) > 0)
    {
        excludes.erase(subject);
    }
}

string Query::getIncludes()
{
    string includes = "";

    for (auto &subject : this->includes)
    {
        includes = includes + subject + ", ";
    }

    return includes;
}

string Query::getExcludes()
{
    string excludes = "";

    for (auto &subject : this->excludes)
    {
        excludes = excludes + subject + ", ";
    }

    return excludes;
}

set<string> Query::getExcludesSet()
{
    return this->excludes;
}
set<string> Query::getIncludesSet()
{
    return this->includes;
}