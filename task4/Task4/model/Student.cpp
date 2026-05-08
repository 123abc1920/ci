#include "Student.h"

std::string Student::getName() const
{
    return name;
}

std::string Student::getSubjects() const
{
    std::string result;

    for (const auto &subject : subjects)
    {
        if (!result.empty())
        {
            result += ", ";
        }
        result += subject;
    }
    return result;
}

void Student::addSubject(const std::string &newSubject)
{
    subjects.insert(newSubject);
}

const std::set<std::string> &Student::getAllSubjects() const
{
    return subjects;
}

bool Student::isLearnSubject(const std::string &subject) const
{
    return subjects.count(subject) > 0;
}
