#include "Student.h";

string Student::getName() const
{
    return name;
}

string Student::getSubjects() const
{
    string result;

    for (auto it = subjects.begin(); it != subjects.end(); ++it)
    {
        if (it != subjects.begin())
            result += ", ";
        result += *it;
    }

    return result;
}
void Student::addSubject(const string &newSubject)
{
    subjects.insert(newSubject);
}

const set<string> &Student::getAllSubjects() const
{
    return subjects;
}

bool Student::isLearnSubject(string subject)
{
    auto count = this->subjects.count(subject);
    if (count > 0)
    {
        return true;
    }
    return false;
}