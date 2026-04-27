#include "FileReader.h"

map<int, Student> FileReader::readDB(string data)
{
    map<int, Student> result;

    auto strs = parse(data);
    int i = 0;
    for (auto &[name, subjects] : strs)
    {
        Student s(name);
        for (auto &subject : subjects)
        {
            s.addSubject(subject);
        }
        result.insert({i, s});
        i++;
    }

    return result;
}

map<string, vector<string>> FileReader::parse(const string &data)
{
    map<string, vector<string>> m;

    int i = 0;
    while (i < data.size())
    {
        while (i < data.size() && (data[i] == '\n' || data[i] == '\r'))
            i++;
        if (i >= data.size())
            break;

        string name;
        while (i < data.size() && data[i] != ' ' && data[i] != '\t' && data[i] != '\n')
        {
            name += data[i++];
        }

        while (i < data.size() && (data[i] == ' ' || data[i] == '\t'))
            i++;

        string subj;
        while (i < data.size() && data[i] != '\n' && data[i] != '\r')
        {
            subj += data[i++];
        }

        if (!name.empty() && !subj.empty())
        {
            m[name].push_back(subj);
        }
    }

    return m;
}