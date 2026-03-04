#ifndef BOOK_H
#define BOOK_H

#include "Printable.h"

class Book : public Printable
{
private:
    int id;
    int time;
    bool isInLib;
    int timeUntilEnd;
    int readerId;

public:
    Book();
    Book(int _id);

    bool isAvailable();
    bool isLost();
    bool isForgotten();

    void setAvailable(bool isAvailbale);
    void setReaderId(int id);

    void setLost();

    int getReaderId();
    int getTimeUntilend();
    void bookDay();

    void giveBook(int readerId);
    void returnBook();
    void print(std::ofstream &report) override;
};

#endif