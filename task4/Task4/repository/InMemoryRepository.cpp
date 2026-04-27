#include "InMemoryRepository.h"

InMemoryRepository::InMemoryRepository()
{
}

void InMemoryRepository::setData(const map<int, Student> &data)
{
    this->inMemoryDB = data;
}

map<int, Student> InMemoryRepository::getAll()
{
    return this->inMemoryDB;
}