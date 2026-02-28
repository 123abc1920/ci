#include "Book.h"
#include <iostream>
#include <cstdlib>

Book::Book()
{
    id = 0;
    time = 3 + rand() % 30;
    timeUntilEnd = time;
    isInLib = true;
    readerId = -1;
}

Book::Book(int _id)
{
    id = _id;
    time = 3 + rand() % 30;
    timeUntilEnd = time;
    isInLib = true;
    readerId = -1;
}

void Book::returnBook()
{
    timeUntilEnd = time;
    isInLib = true;
    readerId = -1;
}

void Book::print(std::ofstream &report)
{
    std::cout << "  ID: " << id << std::endl
              << "  Time until end: " << timeUntilEnd << std::endl;
    report << "  ID: " << id << std::endl
           << "  Time until end: " << timeUntilEnd << std::endl;
}