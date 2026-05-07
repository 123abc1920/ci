#pragma once

#include "FileReader.h"
#include "InMemoryRepository.h"
#include "SubjectsRepository.h"
#include "Query.h"

class MainViewModel
{
private:
    FileReader fileReader;

public:
    MainViewModel(FileReader fileReader);

    InMemoryRepository readDB(string data);
    SubjectsRepository readSubjects(string data);
};