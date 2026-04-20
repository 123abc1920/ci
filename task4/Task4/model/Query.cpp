#include "Query.h"

void Query::addInclude(string subject)
{
    if (includes.count(subject) <= 0)
    {
        includes.insert(subject);
    }
}

void Query::addExclude(string subject)
{
    if (excludes.count(subject) <= 0)
    {
        excludes.insert(subject);
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