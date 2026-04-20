#include <iostream>
#include <set>
#include <string>

using namespace std;

class Query
{
private:
    set<string> includes;
    set<string> excludes;

public:
    void addInclude(string subject)
    {
        if (includes.count(subject) <= 0)
        {
            includes.insert(subject);
        }
    }

    void addExclude(string subject)
    {
        if (excludes.count(subject) <= 0)
        {
            excludes.insert(subject);
        }
    }

    void deleteInclude(string subject)
    {
        while (includes.count(subject) > 0)
        {
            includes.erase(subject);
        }
    }

    void deleteExclude(string subject)
    {
        while (excludes.count(subject) > 0)
        {
            excludes.erase(subject);
        }
    }
};