#include <iostream>
#include <string>
#include <map>
#include "../model/Student.h"

using namespace std;

class InMemoryRepository
{
private:
    map<int, Student> InMemoryDB;

public:
    InMemoryRepository(const map<int, Student> &data)
    {
        InMemoryDB = data;
    }
};