// 9 номер
#include <iostream>

class Printable
{
public:
    Printable() {};

    virtual void print() { std::cout << std::endl; }
};

class Book : Printable
{
public:
    int id;
    int time;
    bool isInLib;

    Book()
    {
        id = 0;
        time = 3 + rand() % 30;
        isInLib = true;
    }

    Book(int _id)
    {
        id = _id;
        time = 3 + rand() % 30;
        isInLib = true;
    }

    void print() override
    {
        std::cout << "ID: " << id << std::endl
                  << "Read time: " << time << std::endl;
    }
};

class Reader : Printable
{
public:
    int id;
    Book *books;
    int *neededBooks;
    int neededBooksCount;
    int availableBooksCount = 0;

    Reader() {}

    Reader(int _id)
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

    void releaseReader()
    {
        delete[] neededBooks;
        delete[] books;
    }

    void print() override
    {
        std::cout << "Reader ID: " << id << std::endl;
        std::cout << "Books: " << std::endl;
        for (int i = 0; i < availableBooksCount; i++)
        {
            books[i].print();
        }
        std::cout << std::endl;
    }
};

class NormalReader : public Reader
{
public:
    NormalReader(int _id) : Reader(_id)
    {
        id = _id;

        int bookCount = 1 + rand() % 5;
        neededBooks = new int[bookCount];
        for (int i = 0; i < bookCount; i++)
        {
            neededBooks[i] = 1 + rand() % 30;
        }
    }
};

class CarelessReader : public Reader
{
public:
    CarelessReader(int _id) : Reader(_id)
    {
        id = _id;

        int bookCount = 1 + rand() % 5;
        neededBooks = new int[bookCount];
        for (int i = 0; i < bookCount; i++)
        {
            neededBooks[i] = 1 + rand() % 30;
        }
    }
};

class GreadyReader : public Reader
{
public:
    GreadyReader(int _id) : Reader(_id)
    {
        id = _id;

        int bookCount = 5 + rand() % 10;
        neededBooks = new int[bookCount];
        for (int i = 0; i < bookCount; i++)
        {
            neededBooks[i] = 1 + rand() % 30;
        }
    }
};

class Library : Printable
{
public:
    Book *books;
    int bookCount;

    Library()
    {
        bookCount = 40 + rand() % 80;
        books = new Book[bookCount];

        for (int i = 0; i < bookCount; i++)
        {
            Book book(i);
            *(books + i) = book;
        }
    }

    void releaseBooks()
    {
        delete[] books;
    }

    bool bookIsAvailable(int ind)
    {
        return books[ind].isInLib;
    }

    int inBookCount()
    {
        int count = 0;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].isInLib)
            {
                count++;
            }
        }

        return count;
    }

    void printStatisctic()
    {
        std::cout << "Statistics:" << std::endl
                  << inBookCount() << "/" << bookCount << " books in library";
    }

    void print() override
    {
        std::cout << "Books:" << std::endl;

        for (int i = 0; i < bookCount; i++)
        {
            books[i].print();
            std::cout << std::endl;
        }
    }
};

int main()
{
    Library lib;

    NormalReader normal1(1);
    for (int i = 0; i < normal1.neededBooksCount; i++)
    {
        if (lib.bookIsAvailable(i))
        {
            normal1.availableBooksCount++;
        }
    }
    normal1.books = new Book[normal1.availableBooksCount];
    for (int i = 0; i < normal1.neededBooksCount; i++)
    {
        if (lib.bookIsAvailable(i))
        {
            normal1.books[i] = lib.books[i];
        }
    }

    GreadyReader gready1(2);
    for (int i = 0; i < gready1.neededBooksCount; i++)
    {
        if (lib.bookIsAvailable(i))
        {
            gready1.availableBooksCount++;
        }
    }
    gready1.books = new Book[gready1.availableBooksCount];
    for (int i = 0; i < gready1.neededBooksCount; i++)
    {
        if (lib.bookIsAvailable(i))
        {
            gready1.books[i] = lib.books[i];
        }
    }

    CarelessReader careless1(3);
    for (int i = 0; i < careless1.neededBooksCount; i++)
    {
        if (lib.bookIsAvailable(i))
        {
            careless1.availableBooksCount++;
        }
    }
    careless1.books = new Book[careless1.availableBooksCount];
    for (int i = 0; i < careless1.neededBooksCount; i++)
    {
        if (lib.bookIsAvailable(i))
        {
            careless1.books[i] = lib.books[i];
        }
    }

    return 0;
}