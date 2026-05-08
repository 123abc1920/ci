#include "Finder.h"

Finder::Finder(const Query &q, const InMemoryRepository &repo, Logger &logger)
    : ILoggable(logger), query(q), repository(repo)
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

    this->writeLog(Logger::Level::DEBUG, "Начат поиск в БД");

    auto data = repository.getAll();

    for (auto &[id, student] : data)
    {
        if (hasIncludes(student))
        {
            results.push_back(student.getName() + " " + student.getSubjects());
        }
    }

    this->writeLog(Logger::Level::INFO, "Поиск завершен, найдено " + std::to_string(results.size()) + " студентов");

    return results;
}

Finder::~Finder()
{
}