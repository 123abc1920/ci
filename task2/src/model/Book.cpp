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

void Book::giveBook(int readerId)
{
    this->isInLib = false;
    this->readerId = readerId;
}

bool Book::isAvailable()
{
    return this->isInLib;
}

bool Book::isLost()
{
    if (!this->isInLib && this->readerId == -1)
    {
        return true;
    }
    return false;
}

bool Book::isForgotten()
{
    if (!this->isInLib && this->readerId != -1 && this->timeUntilEnd < 0)
    {
        return true;
    }
    return false;
}

int Book::getReaderId()
{
    return this->readerId;
}

void Book::setReaderId(int id)
{
    this->readerId = id;
}

void Book::setAvailable(bool isAvailable)
{
    this->isInLib = isAvailable;
}

void Book::bookDay()
{
    this->timeUntilEnd--;
}

void Book::setLost()
{
    this->isInLib = false;
    this->readerId = -1;
}

int Book::getTimeUntilend()
{
    return this->timeUntilEnd;
}

void Book::print(std::ofstream &report)
{
    std::cout << "  ID: " << id << std::endl
              << "  Time until end: " << timeUntilEnd << std::endl;
    report << "  ID: " << id << std::endl
           << "  Time until end: " << timeUntilEnd << std::endl;
}