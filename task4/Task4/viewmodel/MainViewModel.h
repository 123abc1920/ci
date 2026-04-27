#pragma once

#include "FileReader.h"
#include "InMemoryRepository.h"

class MainViewModel
{
private:
    FileReader fileReader;
    InMemoryRepository repository;

public:
    MainViewModel(FileReader fileReader, InMemoryRepository inMemoryRepository);

    void readDB(string data);
    map<int, Student> getAllStudents();
};