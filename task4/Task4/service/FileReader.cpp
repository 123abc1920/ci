#include "FileReader.h"
#include <QDebug>

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

map<int, string> FileReader::readSubjects(string data)
{
    map<int, string> result;
    set<string> preResult;

    int pos = 0;
    while (pos < data.length())
    {
        size_t nameEnd = data.find_first_of(" \t\n", pos);
        if (nameEnd == string::npos)
            break;

        size_t subjectStart = data.find_first_not_of(" \t", nameEnd);
        if (subjectStart == string::npos)
            break;

        size_t subjectEnd = data.find('\n', subjectStart);
        if (subjectEnd == string::npos)
            subjectEnd = data.length();

        string subject = data.substr(subjectStart, subjectEnd - subjectStart);

        while (!subject.empty() && isspace(subject.back()))
        {
            subject.pop_back();
        }

        if (!subject.empty())
        {
            preResult.insert(subject);
        }

        pos = subjectEnd + 1;
    }

    int i = 0;
    for (const auto &subject : preResult)
    {
        result.insert({i++, subject});
    }

    return result;
}