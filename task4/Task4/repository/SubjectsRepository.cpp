#include "SubjectsRepository.h"
#include <QDebug>

SubjectsRepository::SubjectsRepository() {}

void SubjectsRepository::setData(const map<int, string> &data)
{
    this->inMemoryDB = data;
}

vector<string> SubjectsRepository::getAll()
{
    vector<string> result;

    for (const auto &pair : inMemoryDB)
    {
        result.push_back(pair.second);
    }

    return result;
}