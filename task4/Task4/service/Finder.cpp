#include "Finder.h"
#include <algorithm>
#include <iterator>

Finder::Finder(const Query &q, const InMemoryRepository &repo, Logger &logger)
    : ILoggable(logger), query(q), repository(repo) {}

bool Finder::match(const Student &s) const
{
    const auto &studentSubjects = s.getAllSubjects();
    const auto &required = this->query.getIncludesSet();
    const auto &excludes = this->query.getExcludesSet();

    bool hasAllIncludes = std::includes(studentSubjects.begin(), studentSubjects.end(),
                                        required.begin(), required.end());

    if (!hasAllIncludes)
        return false;

    bool hasAnyExcludes = std::any_of(excludes.begin(), excludes.end(),
                                      [&studentSubjects](const std::string &sub)
                                      {
                                          return studentSubjects.find(sub) != studentSubjects.end();
                                      });

    return !hasAnyExcludes;
}

std::vector<std::string> Finder::find() const
{
    std::vector<std::string> results;
    writeLog(Logger::Level::DEBUG, "Начат поиск в БД");

    const auto &data = repository.getAll();

    for (const auto &[id, student] : data)
    {
        if (match(student))
        {
            results.push_back(student.getName() + ": " + student.getSubjects());
        }
    }

    writeLog(Logger::Level::INFO, "Поиск завершен, найдено " + std::to_string(results.size()));
    return results;
}
