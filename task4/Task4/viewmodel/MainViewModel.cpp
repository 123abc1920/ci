#include "MainViewModel.h"
#include <QDebug>

MainViewModel::MainViewModel(FileReader &fileReader, Saver &saver) : fileReader(fileReader), saver(saver)
{
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

bool MainViewModel::save(vector<string> data, string filePath)
{
    return this->saver.save(data, filePath);
}