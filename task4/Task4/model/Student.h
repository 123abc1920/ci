#pragma once

#include <set>
#include <string>

class Student
{
private:
    std::string name;
    std::set<std::string> subjects;

public:
    explicit Student(const std::string &_name) : name(_name) {}

    std::string getName() const;
    std::string getSubjects() const;
    void addSubject(const std::string &newSubject);
    const std::set<std::string> &getAllSubjects() const;
    bool isLearnSubject(const std::string &subject) const;
};
