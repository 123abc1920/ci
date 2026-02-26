// 9 номер
#include <iostream>
#include <thread>
#include <chrono>

class Dayable
{
public:
    Dayable() {};

    virtual void day() {};
};

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

    void returnBook()
    {
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

    void day() override
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
        this->print();
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

    void day() override
    {
        for (int i = 0; i < availableBooksCount; i++)
        {
            int loseBook = 0 + rand() % LOSING_PROBABILITY;
            if (books[i]->isInLib == false && books[i]->readerId == this->id)
            {
                if (books[i]->timeUntilEnd <= 0)
                {
                    int returnOrNot = 0 + rand() % 10;
                    if (returnOrNot < 2)
                    {
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
                if (books[i]->readerId == this->id)
                {
                    books[i]->timeUntilEnd--;
                }
            }
        }
        this->print();
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

class Library : Printable, Dayable
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

    void giveBooks(Reader &r, Library &lib)
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

    void initLibrary()
    {
        int normalCount;
        std::cout << "Normal readers: ";
        std::cin >> normalCount;
        int greadyCount;
        std::cout << "Gready readers: ";
        std::cin >> greadyCount;
        int carelessCount;
        std::cout << "Careless readers: ";
        std::cin >> carelessCount;

        readerCount = normalCount + greadyCount + carelessCount;
        for (int i = 0; i < normalCount; i++)
        {
            readers[i] = new NormalReader(i);
            giveBooks(*readers[i], *this);
        }
        for (int i = normalCount; i < normalCount + greadyCount; i++)
        {
            readers[i] = new GreadyReader(i);
            giveBooks(*readers[i], *this);
        }
        for (int i = normalCount + greadyCount; i < readerCount; i++)
        {
            readers[i] = new CarelessReader(i);
            giveBooks(*readers[i], *this);
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

    int lostBookCount()
    {
        int count = 0;

        for (int i = 0; i < bookCount; i++)
        {
            if (!books[i].isInLib && books[i].readerId == -1)
            {
                count++;
            }
        }

        return count;
    }

    int forgottenBookCount()
    {
        int count = 0;

        for (int i = 0; i < bookCount; i++)
        {
            if (!books[i].isInLib && books[i].readerId != -1 && books[i].timeUntilEnd < 0)
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

    void print() override
    {
        std::cout << " In library now: " << inBookCount() << "/" << bookCount << std::endl
                  << " Lost: " << lostBookCount() << std::endl
                  << " Forgotten: " << forgottenBookCount() << std::endl;
        std::cout << std::endl;
    }

    void day() override
    {
        for (int i = 0; i < readerCount; i++)
        {
            readers[i]->day();
        }
        this->print();
    }
};

void getBook(int readerId, Book &book)
{
    book.readerId = readerId;
    book.isInLib = false;
}

void lifecycle(int lifetime, Library &lib)
{
    for (int i = 0; i < lifetime; i++)
    {
        std::cout << "Day " << i << ":" << std::endl;
        lib.day();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

const int lifetime = 50;
int main()
{
    Library lib;
    lib.initLibrary();

    lifecycle(lifetime, lib);

    lib.release();
    return 0;
}