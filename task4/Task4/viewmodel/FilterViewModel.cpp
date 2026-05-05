#include "FilterViewModel.h"
#include <QDebug>

FilterViewModel::FilterViewModel(const SubjectsRepository &subjectsRepository)
{
    this->subjectsRepository = subjectsRepository;
    qDebug() << "noUI:" << this->subjectsRepository.getAll().size();
}

void FilterViewModel::addToQuery(string subject, bool isExclude)
{
    if (isExclude == true)
    {
        this->mainQuery.addExclude(subject);
    }
    else
    {
        this->mainQuery.addInclude(subject);
    }
}

void FilterViewModel::removeFromQuery(string subject, bool isExclude)
{
    if (isExclude == true)
    {
        this->mainQuery.deleteExclude(subject);
    }
    else
    {
        this->mainQuery.deleteInclude(subject);
    }
}

string FilterViewModel::getQueryText()
{
    return "Выбрать студентов, которые изучают " + this->mainQuery.getIncludes() + "но не изучают " + this->mainQuery.getExcludes();
}

set<string> FilterViewModel::getQueryData(bool isExclude)
{
    if (isExclude == true)
    {
        return this->mainQuery.getExcludesSet();
    }
    else
    {
        return this->mainQuery.getIncludesSet();
    }
}

vector<string> FilterViewModel::getSubjects()
{
    return this->subjectsRepository.getAll();
}

set<string> FilterViewModel::getIncludes()
{
    return this->mainQuery.getIncludesSet();
}

set<string> FilterViewModel::getExcludes()
{
    return this->mainQuery.getExcludesSet();
}