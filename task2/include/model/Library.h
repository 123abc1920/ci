#ifndef LIBRARY_H
#define LIBRARY_H

#include "Printable.h"
#include "Dayable.h"
#include "Book.h"
#include "Reader.h"

class Library : Printable, Dayable
{
private:
    double normal;
    double gready;
    double careless;

    Book *books;
    int bookCount;
    Reader **readers;
    int readerCount;

    int inBookCount();
    int lostBookCount();
    int forgottenBookCount();

public:
    Library();

    ~Library();

    void giveBooks(Reader &r, Library &lib);
    void initLibrary();
    bool bookIsAvailable(int ind);
    void printStatistic(std::ofstream &report);

    void print(std::ofstream &report) override;
    void day(std::ofstream &report) override;
};

#endif