#ifndef DEMO_H
#define DEMO_H

#include <iostream>
#include <string>

template <typename T>
class TheSet;

template <typename T>
void printSetInfo(TheSet<T> &set, const std::string &name)
{
    std::cout << name << ":" << std::endl;
    set.print();
}

template <typename T>
void basics(const T &a, const T &b, const T &c)
{
    TheSet<T> set;

    set.add(a);
    set.add(b);
    set.add(c);

    printSetInfo(set, "Set 1");

    set.remove(b);
    std::cout << "Remove " << b << ":" << std::endl;
    set.print();

    std::cout << "Contain " << a << ": " << set.contain(a)
              << ", Contain " << b << ": " << set.contain(b) << std::endl;
}

template <typename T>
void sums(const T &a, const T &b, const T &c, const T &d, const T &e, const T &f, const T &g)
{
    TheSet<T> set;
    set.add(a);
    set.add(b);
    set.add(c);

    TheSet<T> set4;
    set4.add(d);
    set4.add(e);
    set4.add(f);
    set4.add(g);

    printSetInfo(set4, "Set 2");

    std::cout << "set=set+set4: " << std::endl;
    set = set + set4;
    set.print();
}

template <typename T>
void subtractions(const T &a, const T &b, const T &c, const T &d, const T &e, const T &f,
                  const T &g, const T &h, const T &i)
{
    TheSet<T> set;
    set.add(a);
    set.add(b);
    set.add(c);
    set.add(d);
    set.add(e);
    set.add(f);

    TheSet<T> set3;
    set3.add(g);
    set3.add(h);
    set3.add(i);

    printSetInfo(set3, "Set 3");

    std::cout << "set=set-set3: " << std::endl;
    set = set - set3;
    set.print();
}

template <typename T>
void comparing(const T &a, const T &b, const T &c, const T &d, const T &e, const T &f, const T &g, const T &h)
{
    TheSet<T> set;
    set.add(a);
    set.add(b);

    TheSet<T> set4;
    set4.add(c);
    set4.add(d);
    set4.add(e);
    set4.add(f);
    set4.add(g);
    set4.add(h);

    printSetInfo(set, "Set 4");

    std::cout << "set4==set: " << (set == set4) << std::endl;
}

template <typename T>
void clearing(const T &a, const T &b)
{
    TheSet<T> set;
    set.add(a);
    set.add(b);

    std::cout << "Clear set: " << std::endl;
    set.clear();
    std::cout << "Set is empty: " << set.isEmpty() << std::endl
              << "Set: " << std::endl;
    set.print();
}

void intSet()
{
    std::cout << "INT: " << std::endl
              << std::endl;
    basics<int>(1, 2, 3);
    std::cout << std::endl;

    sums<int>(1, 2, 3, 4, 5, 6, 3);
    std::cout << std::endl;

    subtractions<int>(1, 2, 3, 4, 5, 6, 4, 6, 3);
    std::cout << std::endl;

    comparing<int>(1, 5, 1, 2, 3, 4, 5, 6);
    std::cout << std::endl;

    clearing<int>(1, 5);
}

void strSet()
{
    std::cout << "STRING: " << std::endl
              << std::endl;
    basics<std::string>("1", "2", "3");
    std::cout << std::endl;

    sums<std::string>("1", "2", "3", "4", "5", "6", "3");
    std::cout << std::endl;

    subtractions<std::string>("1", "2", "3", "4", "5", "6", "4", "6", "3");
    std::cout << std::endl;

    comparing<std::string>("1", "5", "1", "2", "3", "4", "5", "6");
    std::cout << std::endl;

    clearing<std::string>("1", "5");
}

#endif