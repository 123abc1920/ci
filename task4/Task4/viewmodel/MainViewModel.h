#pragma once

#include "FileReader.h"
#include "InMemoryRepository.h"
#include "Query.h"

class MainViewModel
{
private:
    FileReader fileReader;
    InMemoryRepository repository;
    Query mainQuery;

public:
    MainViewModel(FileReader fileReader, InMemoryRepository inMemoryRepository, Query query);

    void readDB(string data);
    map<int, Student> getAllStudents();
    void addToQuery(string subject, bool isExclude);
    string getQueryText();
    set<string> getQueryData(bool isExclude);
};