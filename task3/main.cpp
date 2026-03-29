// 9 номер
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

    ~TheSet()
    {
        delete[] content;
    }

    void add(T el)
    {
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
        if (shift == true)
        {
            count--;
        }
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

int main()
{
    TheSet<int> set;

    set.add(1);
    set.add(2);
    set.add(3);

    set.print();

    set.remove(2);

    set.print();

    std::cout << set.contain(1) << " " << set.contain(2);

    return 0;
}