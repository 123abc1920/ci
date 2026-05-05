#pragma once

#include "FileReader.h"
#include "InMemoryRepository.h"
#include "SubjectsRepository.h"
#include "Query.h"

class MainViewModel
{
private:
    FileReader fileReader;
    InMemoryRepository repository;
    SubjectsRepository subjectsRepository;
    Query mainQuery;

public:
    MainViewModel(FileReader fileReader, InMemoryRepository inMemoryRepository, Query query, SubjectsRepository subjectsRepository);

    void readDB(string data);
    map<int, Student> getAllStudents();

    SubjectsRepository getSubjectsRepository();
};