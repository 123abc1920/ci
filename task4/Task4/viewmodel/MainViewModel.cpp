#include "MainViewModel.h"
#include <QDebug>

MainViewModel::MainViewModel(FileReader fileReader)
{
    this->fileReader = fileReader;
}

InMemoryRepository MainViewModel::readDB(string data)
{
    auto dataMap = this->fileReader.readDB(data);
    InMemoryRepository repository;
    repository.setData(dataMap);
    return repository;
}

SubjectsRepository MainViewModel::readSubjects(string data)
{
    auto subjectsMap = this->fileReader.readSubjects(data);
    SubjectsRepository subjectsRepository;
    subjectsRepository.setData(subjectsMap);
    return subjectsRepository;
}