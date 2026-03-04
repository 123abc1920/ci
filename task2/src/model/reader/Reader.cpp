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

Reader::~Reader()
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
        if (books[i]->getReaderId() == this->id)
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
        if (books[i]->isAvailable() == false && books[i]->getReaderId() == this->id)
        {
            if (books[i]->getReaderId() == this->id)
            {
                books[i]->bookDay();
            }
            if (books[i]->getTimeUntilend() <= 0)
            {
                int loseBook = 0 + rand() % LOSING_PROBABILITY;
                if (loseBook < LOST_NUMBER)
                {
                    books[i]->setLost();
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

int Reader::getId()
{
    return this->id;
}

int Reader::getNeededBook(int i)
{
    return this->neededBooks[i];
}

void Reader::setBooks(int count)
{
    this->availableBooksCount = count;
    this->books = new Book *[this->availableBooksCount];
}

void Reader::setBook(int index, Book &book)
{
    this->books[index] = &book;
}

void Reader::setNeededBookCount(int count)
{
    if (count < 0)
    {
        count = 0;
    }
    this->neededBooksCount = count;
};

void Reader::setAvailableBookCount(int count)
{
    if (count < 0)
    {
        count = 0;
    }
    this->availableBooksCount = count;
};

int Reader::getNeededBookCount()
{
    return this->neededBooksCount;
};

int Reader::getAvailableBookCount()
{
    return this->availableBooksCount;
};