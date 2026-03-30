// 9 номер
#include <iostream>
#include "theset.h"

void printSetInfo(TheSet<int> &set, const std::string &name)
{
    std::cout << name << ":" << std::endl;
    set.print();
}

void basics()
{
    TheSet<int> set;

    set.add(1);
    set.add(2);
    set.add(3);

    printSetInfo(set, "Set 1");

    set.remove(2);
    std::cout << "Remove 2:" << std::endl;
    set.print();

    std::cout << "Contain 1: " << set.contain(1)
              << ", Contain 2: " << set.contain(2) << std::endl;
}

void sums()
{
    TheSet<int> set;
    set.add(1);
    set.add(2);
    set.add(3);

    TheSet<int> set2;
    set2.add(4);
    set2.add(5);
    set2.add(6);
    set2.add(3);

    printSetInfo(set2, "Set 2");

    std::cout << "set=set+set2: " << std::endl;
    set = set + set2;
    set.print();
}

void subtractions()
{
    TheSet<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    set.add(4);
    set.add(5);
    set.add(6);

    TheSet<int> set3;
    set3.add(4);
    set3.add(6);
    set3.add(3);

    printSetInfo(set3, "Set 3");

    std::cout << "set=set-set3: " << std::endl;
    set = set - set3;
    set.print();
}

void comparing()
{
    TheSet<int> set;
    set.add(1);
    set.add(5);

    TheSet<int> set2;
    set2.add(1);
    set2.add(2);
    set2.add(3);
    set2.add(4);
    set2.add(5);
    set2.add(6);

    printSetInfo(set, "Set 4");

    std::cout << "set4==set: " << (set == set2) << std::endl;

    std::cout << "Clear set: " << std::endl;
    set2.clear();
    std::cout << "Set is empty: " << set2.isEmpty() << std::endl
              << "Set: " << std::endl;
    set2.print();
}

void intSet()
{
    basics();
    std::cout << std::endl;

    sums();
    std::cout << std::endl;

    subtractions();
    std::cout << std::endl;

    comparing();
}

void strSet()
{
}

int main()
{
    intSet();
    strSet();

    return 0;
}