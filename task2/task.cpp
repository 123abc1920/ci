// 9 номер
#include <iostream>
#include <thread>
#include <chrono>

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
    int timeUntilEnd;
    int readerId;

    Book()
    {
        id = 0;
        time = 3 + rand() % 30;
        timeUntilEnd = time;
        isInLib = true;
        readerId = -1;
    }

    Book(int _id)
    {
        id = _id;
        time = 3 + rand() % 30;
        timeUntilEnd = time;
        isInLib = true;
        readerId = -1;
    }

    void print() override
    {
        std::cout << "  ID: " << id << std::endl
                  << "  Time until end: " << timeUntilEnd << std::endl;
    }
};

class Reader : Printable
{
public:
    int id;
    Book **books = nullptr;
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
        for (int i = 0; i < availableBooksCount; i++)
        {
            delete books[i];
        }
        delete[] books;
    }

    void day()
    {
        for (int i = 0; i < availableBooksCount; i++)
        {
            if (books[i]->isInLib == this->id)
            {
                books[i]->timeUntilEnd--;
            }
        }
    }

    void print() override
    {
        std::cout << " Reader ID: " << id << std::endl;
        std::cout << " Books: " << std::endl;
        for (int i = 0; i < availableBooksCount; i++)
        {
            if (books[i]->readerId == this->id)
            {
                books[i]->print();
            }
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

        neededBooksCount = 1 + rand() % 5;
        neededBooks = new int[neededBooksCount];
        for (int i = 0; i < neededBooksCount; i++)
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

        neededBooksCount = 1 + rand() % 5;
        neededBooks = new int[neededBooksCount];
        for (int i = 0; i < neededBooksCount; i++)
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

        neededBooksCount = 5 + rand() % 10;
        neededBooks = new int[neededBooksCount];
        for (int i = 0; i < neededBooksCount; i++)
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
    Reader **readers;
    int readerCount;

    Library()
    {
        bookCount = 40 + rand() % 80;
        books = new Book[bookCount];
        readerCount = 3;
        readers = new Reader *[readerCount];

        for (int i = 0; i < readerCount; i++)
        {
            readers[i] = nullptr;
        }

        for (int i = 0; i < bookCount; i++)
        {
            Book book(i);
            *(books + i) = book;
        }
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

    void release()
    {
        delete[] this->books;

        for (int i = 0; i < readerCount; i++)
        {
            if (readers[i] != nullptr)
            {
                readers[i]->releaseReader();
                delete readers[i];
            }
        }
        delete[] readers;
    }

    void printStatisctic()
    {
        std::cout << "Statistics:" << std::endl
                  << inBookCount() << "/" << bookCount << " books in library";
    }

    void print() override
    {
        for (int i = 0; i < readerCount; i++)
        {
            readers[i]->day();
            readers[i]->print();
        }
    }
};

void returnBook(Reader &r, Book &b)
{
    b.isInLib = true;
    b.readerId = -1;
    b.timeUntilEnd = b.time;
}

void getBooks(Reader &r, Library &lib)
{
    int *booksIndexes = new int[r.neededBooksCount];
    int j = 0;
    for (int i = 0; i < r.neededBooksCount; i++)
    {
        if (lib.bookIsAvailable(r.neededBooks[i]))
        {
            r.availableBooksCount++;
            booksIndexes[j] = i;
            j++;
        }
    }

    r.books = new Book *[r.availableBooksCount];
    for (int i = 0; i < r.availableBooksCount; i++)
    {
        r.books[i] = &lib.books[booksIndexes[i]];
        lib.books[booksIndexes[i]].isInLib = false;
        lib.books[booksIndexes[i]].readerId = r.id;
    }
    delete[] booksIndexes;
}

int main()
{
    int lifetime = 50;

    Library lib;

    lib.readers[0] = new NormalReader(1);
    getBooks(*lib.readers[0], lib);

    lib.readers[1] = new GreadyReader(2);
    getBooks(*lib.readers[1], lib);

    lib.readers[2] = new CarelessReader(3);
    getBooks(*lib.readers[2], lib);

    for (int i = 0; i < lifetime; i++)
    {
        std::cout << "Day " << i << ":" << std::endl;
        lib.print();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    lib.release();
    return 0;
}