#include "InMemoryRepository.h"

void InMemoryRepository::setData(const std::map<int, Student> &data)
{
    this->inMemoryDB = data;
}

const std::map<int, Student> &InMemoryRepository::getAll() const
{
    return this->inMemoryDB;
}
