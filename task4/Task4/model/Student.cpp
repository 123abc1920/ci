#include <iostream>
#include <set>
#include <string>

using namespace std;

class Student
{
private:
    string name;
    set<string> subjects;

public:
    Student(const string &_name) : name(_name) {}

    string getName() const
    {
        return name;
    }

    void addSubject(const string &newSubject)
    {
        subjects.insert(newSubject);
    }

    const set<string> &getAllSubjects() const
    {
        return subjects;
    }

    bool isLearnSubject(string subject)
    {
        auto count = this->subjects.count(subject);
        if (count > 0)
        {
            return true;
        }
        return false;
    }
};