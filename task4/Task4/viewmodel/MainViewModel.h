#pragma once

#include "FileReader.h"
#include "Saver.h"
#include "SubjectsRepository.h"
#include "InMemoryRepository.h"
#include "Logger.h"
#include "BaseViewModel.h"

class MainViewModel : public BaseViewModel
{
private:
    FileReader &fileReader;
    Saver &saver;

public:
    MainViewModel(FileReader &fileReader, Saver &saver, Logger &logger);

    InMemoryRepository readDB(string data);
    SubjectsRepository readSubjects(string data);
    bool save(vector<string> data, string filePath);
};