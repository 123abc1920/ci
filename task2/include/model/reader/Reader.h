#ifndef READER_H
#define READER_H

#include "Book.h"
#include "Dayable.h"

class Reader : Printable, Dayable
{
public:
    int id;
    Book **books = nullptr;
    int *neededBooks;
    int neededBooksCount;
    int availableBooksCount = 0;

    const int LOSING_PROBABILITY = 50;
    const int LOST_NUMBER = 5;

    Reader();
    Reader(int _id);

    void releaseReader();
    void print(std::ofstream &report) override;
    void day(std::ofstream &report) override;
};

#endif