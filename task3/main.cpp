// 9 номер
#include <iostream>
#include "theset.h"

int main()
{
    TheSet<int> set;

    set.add(1);
    set.add(2);
    set.add(3);

    set.print();

    set.remove(2);

    set.print();

    std::cout << set.contain(1) << " " << set.contain(2) << std::endl;

    TheSet<int> set2;

    set2.add(4);
    set2.add(5);
    set2.add(6);
    set2.add(3);

    set2.print();

    set = set + set2;

    set.print();

    TheSet<int> set3;

    set3.add(4);
    set3.add(6);
    set3.add(3);

    set3.print();

    set = set - set3;
    std::cout << set.isEmpty() << std::endl;
    set.print();

    TheSet<int> set4;
    set4.add(1);
    set4.add(5);

    std::cout << (set4 == set) << std::endl;

    set.clear();
    std::cout << set.isEmpty() << std::endl;
    set.print();

    return 0;
}