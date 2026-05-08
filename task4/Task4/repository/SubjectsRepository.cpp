#include "SubjectsRepository.h"
#include <algorithm>
#include <iterator>

void SubjectsRepository::setData(const std::map<int, std::string> &data)
{
    database = data;
}

std::vector<std::string> SubjectsRepository::getAll() const
{
    std::vector<std::string> result;

    result.reserve(database.size());

    for (const auto &[id, name] : database)
    {
        result.push_back(name);
    }

    return result;
}
