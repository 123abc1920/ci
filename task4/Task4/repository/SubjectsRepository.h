#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class SubjectsRepository
{
private:
    map<int, string> inMemoryDB;

public:
    SubjectsRepository();

    void setData(const map<int, string> &data);
    vector<string> getAll();
};