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

std::string FilterViewModel::getQueryText() const
{
    return "Выбрать студентов, которые изучают " + query.getIncludes() +
           " но не изучают " + query.getExcludes();
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
