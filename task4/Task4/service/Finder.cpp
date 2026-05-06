#include "Finder.h"

Finder::Finder(Query &q, InMemoryRepository &repo)
    : query(q), repository(repo)
{
}

bool Finder::notHasExcludes(Student &s)
{
    for (const auto &subject : query.getExcludesSet())
    {
        if (s.isLearnSubject(subject))
            return false;
    }
    return true;
}

bool Finder::hasIncludes(Student &s)
{
    for (const auto &subject : query.getIncludesSet())
    {
        if (!s.isLearnSubject(subject))
            return false;
    }
    return notHasExcludes(s);
}

vector<string> Finder::find()
{
    vector<string> results;

    auto data = repository.getAll();

    for (auto &[id, student] : data)
    {
        if (hasIncludes(student))
        {
            results.push_back(student.getName() + " " + student.getSubjects());
        }
    }

    return results;
}
