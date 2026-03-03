#ifndef LIBRARY_H
#define LIBRARY_H

#include "Printable.h"
#include "Dayable.h"
#include "Book.h"
#include "Reader.h"

class Library : Printable, Dayable
{
public:
    Book *books;
    int bookCount;
    Reader **readers;
    int readerCount;

    double normal;
    double gready;
    double careless;

    Library();

    ~Library();

    void giveBooks(Reader &r, Library &lib);
    void initLibrary();
    bool bookIsAvailable(int ind);
    int inBookCount();
    int lostBookCount();
    int forgottenBookCount();
    void printStatistic(std::ofstream &report);

    void print(std::ofstream &report) override;
    void day(std::ofstream &report) override;
};

#endif