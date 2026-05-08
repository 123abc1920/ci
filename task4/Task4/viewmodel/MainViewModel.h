#pragma once

#include "FileReader.h"
#include "Saver.h"
#include "SubjectsRepository.h"
#include "InMemoryRepository.h"
#include "Logger.h"
#include "ILoggable.h"

class MainViewModel : public ILoggable
{
private:
    FileReader &fileReader;
    Saver &saver;

public:
    MainViewModel(FileReader &fileReader, Saver &saver, Logger &logger);

    InMemoryRepository readDB(std::string data);
    SubjectsRepository readSubjects(std::string data);
    bool save(std::vector<std::string> data, std::string filePath);
};