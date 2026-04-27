#pragma once

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

    string getName() const;
    string getSubjects() const;
    void addSubject(const string &newSubject);
    const set<string> &getAllSubjects() const;
    bool isLearnSubject(string subject);
};