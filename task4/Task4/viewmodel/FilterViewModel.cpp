#include "FilterViewModel.h"

FilterViewModel::FilterViewModel(const SubjectsRepository &subjectsRepo,
                                 const InMemoryRepository &repo,
                                 Logger &logger)
    : ILoggable(logger), subjectsRepo(subjectsRepo), repository(repo)
{
}

void FilterViewModel::addToQuery(const std::string &subject, bool isExclude)
{
    if (isExclude)
    {
        query.addExclude(subject);
    }
    else
    {
        query.addInclude(subject);
    }
}

void FilterViewModel::removeFromQuery(const std::string &subject, bool isExclude)
{
    if (isExclude)
    {
        query.deleteExclude(subject);
    }
    else
    {
        query.deleteInclude(subject);
    }
}

#include <sstream>

std::string FilterViewModel::getQueryText() const
{
    auto includes = query.getIncludes();
    auto excludes = query.getExcludes();

    if (includes.empty() && excludes.empty())
    {
        return "Фильтры не заданы (выбраны все студенты)";
    }

    std::ostringstream oss;
    oss << "Выбрать студентов";

    if (!includes.empty())
    {
        oss << ", которые изучают " << includes;
    }

    if (!excludes.empty())
    {
        if (!includes.empty())
        {
            oss << ", но";
        }
        oss << " не изучают " << excludes;
    }

    return oss.str();
}

const std::set<std::string> &FilterViewModel::getQueryData(bool isExclude) const
{
    return isExclude ? query.getExcludesSet() : query.getIncludesSet();
}

std::vector<std::string> FilterViewModel::getSubjects() const
{
    return subjectsRepo.getAll();
}

const std::set<std::string> &FilterViewModel::getIncludes() const
{
    return query.getIncludesSet();
}

const std::set<std::string> &FilterViewModel::getExcludes() const
{
    return query.getExcludesSet();
}
