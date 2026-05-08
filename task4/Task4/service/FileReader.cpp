#include "FileReader.h"
#include <sstream>

FileReader::FileReader(Logger &logger) : ILoggable(logger) {}

std::map<int, Student> FileReader::readDB(std::string_view data)
{
    std::map<int, Student> result;
    writeLog(Logger::Level::DEBUG, "Начато чтение файла");

    auto parsedData = parse(data);
    int id = 0;

    for (auto &[name, subjects] : parsedData)
    {
        Student s(name);
        for (const auto &subject : subjects)
        {
            s.addSubject(subject);
        }
        result.emplace(id++, std::move(s));
    }

    writeLog(Logger::Level::INFO, "Файл считан, студентов " + std::to_string(result.size()));
    return result;
}

std::map<std::string, std::vector<std::string>> FileReader::parse(std::string_view data)
{
    std::map<std::string, std::vector<std::string>> result;
    std::stringstream dataStream{std::string(data)};
    std::string line;

    while (std::getline(dataStream, line))
    {
        if (line.empty())
            continue;

        std::stringstream lineStream(line);
        std::string name;
        std::string subject;

        if (lineStream >> name)
        {
            lineStream >> std::ws;
            std::getline(lineStream, subject);
            if (!subject.empty())
            {
                result[name].push_back(subject);
            }
        }
    }
    return result;
}

std::map<int, std::string> FileReader::readSubjects(std::string_view data)
{
    std::map<int, std::string> result;
    std::set<std::string> subjects;

    writeLog(Logger::Level::DEBUG, "Начат поиск предметов");

    std::stringstream dataStream{std::string(data)};
    std::string line;
    while (std::getline(dataStream, line))
    {
        std::stringstream lineStream(line);
        std::string name, subject;
        if (lineStream >> name)
        {
            lineStream >> std::ws;
            std::getline(lineStream, subject);
            if (!subject.empty())
            {
                subjects.insert(subject);
            }
        }
    }

    int id = 0;
    for (auto &sub : subjects)
    {
        result.emplace(id++, sub);
    }

    writeLog(Logger::Level::INFO, "Найдено " + std::to_string(result.size()) + " предметов");
    return result;
}
