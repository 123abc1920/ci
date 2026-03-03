#include "Library.h"
#include "NormalReader.h"
#include "CarelessReader.h"
#include "GreadyReader.h"

Library::Library()
{
    bookCount = 40 + rand() % 80;
    books = new Book[bookCount];

    for (int i = 0; i < bookCount; i++)
    {
        Book book(i);
        *(books + i) = book;
    }
}

Library::~Library()
{
    delete[] this->books;

    for (int i = 0; i < readerCount; i++)
    {
        if (readers[i] != nullptr)
        {
            delete readers[i];
        }
    }
    delete[] readers;
}

void Library::giveBooks(Reader &r, Library &lib)
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

void Library::initLibrary()
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

    normal = normalCount;
    gready = greadyCount;
    careless = carelessCount;

    readerCount = normalCount + greadyCount + carelessCount;
    readers = new Reader *[readerCount];
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

bool Library::bookIsAvailable(int ind)
{
    return books[ind].isInLib;
}

int Library::inBookCount()
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

int Library::lostBookCount()
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

int Library::forgottenBookCount()
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

void Library::printStatistic(std::ofstream &report)
{
    std::cout << "Summary: " << std::endl
              << " Readers: " << readerCount << std::endl
              << " Lost books count: " << lostBookCount() << std::endl
              << " Normal readers: " << normal << std::endl
              << " Gready readers: " << gready << std::endl
              << " Careless readers: " << careless << std::endl
              << " Lost books list: " << std::endl;
    report << "Summary: " << std::endl
           << " Readers: " << readerCount << std::endl
           << " Lost books: " << lostBookCount() << std::endl
           << " Normal readers: " << normal << std::endl
           << " Gready readers: " << gready << std::endl
           << " Careless readers: " << careless << std::endl
           << " Lost books list: " << std::endl;

    for (int i = 0; i < readerCount; i++)
    {
        if (books[i].isInLib == false && books[i].readerId == -1)
        {
            books[i].print(report);
        }
    }
}

void Library::print(std::ofstream &report)
{
    std::cout << " In library now: " << inBookCount() << "/" << bookCount << std::endl
              << " Lost: " << lostBookCount() << std::endl
              << " Forgotten: " << forgottenBookCount() << std::endl
              << std::endl;
    report << " In library now: " << inBookCount() << "/" << bookCount << std::endl
           << " Lost: " << lostBookCount() << std::endl
           << " Forgotten: " << forgottenBookCount() << std::endl
           << std::endl;
}

void Library::day(std::ofstream &report)
{
    for (int i = 0; i < readerCount; i++)
    {
        readers[i]->day(report);
    }
    this->print(report);
}