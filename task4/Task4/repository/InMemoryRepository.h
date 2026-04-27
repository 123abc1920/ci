#pragma once

#include <iostream>
#include <string>
#include <map>
#include "Student.h"

using namespace std;

class InMemoryRepository
{
private:
    map<int, Student> inMemoryDB;

public:
    InMemoryRepository();

    void setData(const map<int, Student> &data);
    map<int, Student> getAll();
};