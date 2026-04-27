#include "MainViewModel.h"

MainViewModel::MainViewModel(FileReader fileReader, InMemoryRepository inMemoryRepository)
{
    this->fileReader = fileReader;
    this->repository = inMemoryRepository;
}

void MainViewModel::readDB(string data)
{
    auto dataMap = this->fileReader.readDB(data);
    this->repository.setData(dataMap);
}

map<int, Student> MainViewModel::getAllStudents()
{
    return this->repository.getAll();
}