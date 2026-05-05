#include "MainViewModel.h"
#include <QDebug>

MainViewModel::MainViewModel(FileReader fileReader, InMemoryRepository inMemoryRepository, Query query, SubjectsRepository subjectsRepository)
{
    this->fileReader = fileReader;
    this->repository = inMemoryRepository;
    this->mainQuery = query;
    this->subjectsRepository = subjectsRepository;
}

void MainViewModel::readDB(string data)
{
    auto dataMap = this->fileReader.readDB(data);
    this->repository.setData(dataMap);
    auto subjectsMap = this->fileReader.readSubjects(data);
    this->subjectsRepository.setData(subjectsMap);
}

map<int, Student> MainViewModel::getAllStudents()
{
    return this->repository.getAll();
}

SubjectsRepository MainViewModel::getSubjectsRepository()
{
    return this->subjectsRepository;
}