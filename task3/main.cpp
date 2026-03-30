// 9 номер
#include <iostream>
#include "theset.h"

void intSet()
{
    TheSet<int> set;

    set.add(1);
    set.add(2);
    set.add(3);

    std::cout << "Set 1:" << std::endl;
    set.print();

    set.remove(2);

    std::cout << "Remove 2:" << std::endl;
    set.print();

    std::cout << "Contain 1: " << set.contain(1) << ", Contain 2: " << set.contain(2) << std::endl;

    TheSet<int> set2;

    set2.add(4);
    set2.add(5);
    set2.add(6);
    set2.add(3);

    std::cout << "Set 2:" << std::endl;
    set2.print();

    std::cout << "set=set+st2: " << std::endl;
    set = set + set2;
    set.print();

    TheSet<int> set3;

    set3.add(4);
    set3.add(6);
    set3.add(3);

    std::cout << "Set 3:" << std::endl;
    set3.print();

    std::cout << "set=set-st3: " << std::endl;
    set = set - set3;
    set.print();

    std::cout << "set is empty: " << set.isEmpty() << std::endl;

    TheSet<int> set4;
    set4.add(1);
    set4.add(5);
    std::cout << "Set 4:" << std::endl;
    set4.print();

    std::cout << "set4==set: " << (set4 == set) << std::endl;

    std::cout << "Clear set: " << std::endl;
    set.clear();
    std::cout << "Set is empty: " << set.isEmpty() << std::endl
              << "Set: " << std::endl;
    set.print();
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