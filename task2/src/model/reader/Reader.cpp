#include "Reader.h"
#include "Dayable.h"

Reader::Reader()
{
    id = 0;
    int bookCount = 1 + rand() % 5;
    neededBooksCount = bookCount;
    neededBooks = new int[bookCount];
    for (int i = 0; i < bookCount; i++)
    {
        neededBooks[i] = 1 + rand() % 30;
    }
}

Reader::Reader(int _id)
{
    id = _id;
    int bookCount = 1 + rand() % 5;
    neededBooksCount = bookCount;
    neededBooks = new int[bookCount];
    for (int i = 0; i < bookCount; i++)
    {
        neededBooks[i] = 1 + rand() % 30;
    }
}

void Reader::releaseReader()
{
    delete[] neededBooks;
    delete[] books;
}

void Reader::print(std::ofstream &report)
{
    std::cout << " Reader ID: " << id << std::endl
              << " Books: " << std::endl;
    report << " Reader ID: " << id << std::endl
           << " Books: " << std::endl;
    for (int i = 0; i < availableBooksCount; i++)
    {
        if (books[i]->readerId == this->id)
        {
            books[i]->print(report);
        }
    }
    std::cout << std::endl;
    report << std::endl;
}

void Reader::day(std::ofstream &report)
{
    for (int i = 0; i < availableBooksCount; i++)
    {
        if (books[i]->isInLib == false && books[i]->readerId == this->id)
        {
            if (books[i]->readerId == this->id)
            {
                books[i]->timeUntilEnd--;
            }
            if (books[i]->timeUntilEnd <= 0)
            {
                int loseBook = 0 + rand() % LOSING_PROBABILITY;
                if (loseBook < LOST_NUMBER)
                {
                    books[i]->isInLib = false;
                    books[i]->readerId = -1;
                }
                else
                {
                    books[i]->returnBook();
                }
            }
        }
    }
    this->print(report);
}