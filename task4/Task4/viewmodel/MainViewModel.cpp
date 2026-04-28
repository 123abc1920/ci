#include "MainViewModel.h"

MainViewModel::MainViewModel(FileReader fileReader, InMemoryRepository inMemoryRepository, Query query)
{
    this->fileReader = fileReader;
    this->repository = inMemoryRepository;
    this->mainQuery = query;
}

void MainViewModel::readDB(string data)
{
    auto dataMap = this->fileReader.readDB(data);
    this->repository.setData(dataMap);
}

map<int, Student> MainViewModel::getAllStudents()
{
    return this->repository.getAll();
}

void MainViewModel::addToQuery(string subject, bool isExclude)
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

void MainViewModel::removeFromQuery(string subject, bool isExclude)
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

string MainViewModel::getQueryText()
{
    return "Выбрать студентов, которые изучают " + this->mainQuery.getIncludes() + "но не изучают " + this->mainQuery.getExcludes();
}

set<string> MainViewModel::getQueryData(bool isExclude)
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