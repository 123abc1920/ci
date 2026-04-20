#include <iostream>
#include <string>
#include <map>
#include "../model/Student.h"

using namespace std;

class FileReader
{
public:
    map<int, Student> readDB(string path);
};