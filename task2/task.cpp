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

    void release()
    {
        delete[] this->books;
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

    r.books = new Book[r.availableBooksCount];
    for (int i = 0; i < r.availableBooksCount; i++)
    {
        r.books[i] = lib.books[booksIndexes[i]];
        lib.books[booksIndexes[i]].isInLib = false;
    }
    delete[] booksIndexes;
}

int main()
{
    Library lib;
    Reader *readers = new Reader[3];

    NormalReader normal1(1);
    getBooks(normal1, lib);
    readers[0] = normal1;

    GreadyReader gready1(2);
    getBooks(gready1, lib);
    readers[1] = gready1;

    CarelessReader careless1(3);
    getBooks(careless1, lib);
    readers[2] = careless1;

    lib.release();
    for (int i = 0; i < 3; i++)
    {
        readers[i].releaseReader();
    }
    delete[] readers;

    std::cout << "Success";
    return 0;
}