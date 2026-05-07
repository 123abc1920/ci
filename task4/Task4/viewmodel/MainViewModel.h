#pragma once

#include "FileReader.h"
#include "Saver.h"
#include "SubjectsRepository.h"
#include "InMemoryRepository.h"

class MainViewModel
{
private:
    FileReader &fileReader;
    Saver &saver;

public:
    MainViewModel(FileReader &fileReader, Saver &saver);

    InMemoryRepository readDB(string data);
    SubjectsRepository readSubjects(string data);
    bool save(vector<string> data, string filePath);
};