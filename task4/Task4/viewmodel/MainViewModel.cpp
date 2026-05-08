#include "MainViewModel.h"
#include <QDebug>

MainViewModel::MainViewModel(FileReader &fileReader, Saver &saver, Logger &logger)
    : ILoggable(logger), fileReader(fileReader), saver(saver) {}

InMemoryRepository MainViewModel::readDB(std::string data)
{
    auto dataMap = this->fileReader.readDB(data);
    InMemoryRepository repository;
    repository.setData(dataMap);
    return repository;
}

SubjectsRepository MainViewModel::readSubjects(std::string data)
{
    auto subjectsMap = this->fileReader.readSubjects(data);
    SubjectsRepository subjectsRepository;
    subjectsRepository.setData(subjectsMap);
    return subjectsRepository;
}

bool MainViewModel::save(std::vector<std::string> data, std::string filePath)
{
    return this->saver.save(data, filePath);
}