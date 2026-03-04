#ifndef READER_H
#define READER_H

#include "Book.h"
#include "Dayable.h"

class Reader : Printable, Dayable
{
protected:
    int id;
    int *neededBooks;
    Book **books = nullptr;
    int neededBooksCount;
    int availableBooksCount = 0;

    const int LOSING_PROBABILITY = 50;
    const int LOST_NUMBER = 5;

public:
    Reader();
    Reader(int _id);

    ~Reader();

    int getId();
    int getNeededBook(int i);
    void setBooks(int count);
    void setBook(int index, Book &book);

    void setNeededBookCount(int count);
    void setAvailableBookCount(int count);
    int getNeededBookCount();
    int getAvailableBookCount();

    void print(std::ofstream &report) override;
    void day(std::ofstream &report) override;
};

#endif