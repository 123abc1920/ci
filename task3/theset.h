#ifndef THESET_H
#define THESET_H

#include <iostream>

template <typename T>
class TheSet
{
private:
    T *content;

    int count = 0;
    int length = 0;

    int const BASE_COUNT = 10;

    void updLength()
    {
        length += BASE_COUNT;
        T *temp = new T[length];

        for (int i = 0; i < count; i++)
        {
            temp[i] = content[i];
        }

        delete[] content;
        content = temp;
    }

public:
    TheSet()
    {
        content = new T[BASE_COUNT];
        length = BASE_COUNT;
    }

    TheSet(const TheSet &other)
    {
        length = other.length;
        count = other.count;
        content = new T[length];
        for (int i = 0; i < count; i++)
        {
            content[i] = other.content[i];
        }
    }

    ~TheSet()
    {
        delete[] content;
    }

    void add(T el)
    {
        for (int i = 0; i < count; i++)
        {
            if (content[i] == el)
            {
                return;
            }
        }

        if (count + 1 > length)
        {
            updLength();
        }
        content[count] = el;
        count++;
    }

    bool contain(T el)
    {
        for (int i = 0; i < count; i++)
        {
            if (content[i] == el)
            {
                return true;
            }
        }
        return false;
    }

    void remove(T el)
    {
        bool shift = false;
        for (int i = 0; i < count - 1; i++)
        {
            if (content[i] == el)
            {
                shift = true;
            }
            if (shift == true)
            {
                content[i] = content[i + 1];
            }
        }
        if (content[count - 1] == el)
        {
            shift = true;
        }
        if (shift == true)
        {
            count--;
        }
    }

    void clear()
    {
        delete[] content;
        content = new T[BASE_COUNT];
        count = 0;
        length = BASE_COUNT;
    }

    bool isEmpty()
    {
        if (count == 0)
        {
            return true;
        }
        return false;
    }

    const T *getAll() const
    {
        return content;
    }

    int size() const
    {
        return count;
    }

    TheSet &operator=(const TheSet &other)
    {
        if (this != &other)
        {
            delete[] content;
            length = other.length;
            count = other.count;
            content = new T[length];
            for (int i = 0; i < count; i++)
            {
                content[i] = other.content[i];
            }
        }
        return *this;
    }

    TheSet operator+(const TheSet &other)
    {
        TheSet result = *this;

        const T *newEls = other.getAll();
        int size = other.size();

        for (int i = 0; i < size; i++)
        {
            bool exists = false;
            for (int j = 0; j < result.size(); j++)
            {
                if (result.content[j] == newEls[i])
                {
                    exists = true;
                    break;
                }
            }
            if (!exists)
            {
                result.add(newEls[i]);
            }
        }
        return result;
    }

    TheSet operator-(const TheSet &other)
    {
        TheSet result = *this;

        const T *newEls = other.getAll();
        int size = other.size();

        for (int i = 0; i < size; i++)
        {
            result.remove(newEls[i]);
        }
        return result;
    }

    bool operator==(const TheSet &other)
    {
        TheSet result = *this;

        const T *newEls = other.getAll();
        int size = other.size();

        for (int i = 0; i < size; i++)
        {
            if (!result.contain(newEls[i]))
            {
                return false;
            }
        }

        return true;
    }

    void print()
    {
        for (int i = 0; i < count; i++)
        {
            std::cout << content[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif