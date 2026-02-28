#ifndef BOOK_H
#define BOOK_H

#include "Printable.h"

class Book : public Printable
{
public:
    int id;
    int time;
    bool isInLib;
    int timeUntilEnd;
    int readerId;

    Book();
    Book(int _id);

    void returnBook();
    void print(std::ofstream& report) override;
};

#endif