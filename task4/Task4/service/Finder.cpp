#include "Finder.h"

Finder::Finder(const Query &q, const InMemoryRepository &repo, Logger &logger)
    : ILoggable(logger), query(q), repository(repo) {}

bool Finder::notHasExcludes(const Student &s) const
{
    for (const auto &subject : this->query.getExcludesSet())
    {
        if (s.isLearnSubject(subject))
            return false;
    }
    return true;
}

bool Finder::hasIncludes(const Student &s) const
{
    for (const auto &subject : this->query.getIncludesSet())
    {
        if (!s.isLearnSubject(subject))
            return false;
    }
    return notHasExcludes(s);
}

std::vector<std::string> Finder::find() const
{
    std::vector<std::string> results;
    this->writeLog(Logger::Level::DEBUG, "Начат поиск в БД");

    const auto &data = this->repository.getAll();

    for (const auto &[id, student] : data)
    {
        if (hasIncludes(student))
        {
            results.push_back(student.getName() + " " + student.getSubjects());
        }
    }

    this->writeLog(Logger::Level::INFO, "Поиск завершен, найдено " + std::to_string(results.size()));
    return results;
}
