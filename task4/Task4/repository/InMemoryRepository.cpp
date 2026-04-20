#include <iostream>
#include <string>
#include <map>

using namespace std;

class InMemoryRepository
{
private:
    map<int, string> InMemoryDB;

public:
    InMemoryRepository(const map<int, string> &data)
    {
        InMemoryDB = data;
    }
};