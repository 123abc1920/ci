#include "Library.h"
#include "NormalReader.h"
#include "CarelessReader.h"
#include "GreedyReader.h"

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
    int *booksIndexes = new int[r.getNeededBookCount()];
    int j = 0;
    int availableBooksCount = 0;
    for (int i = 0; i < r.getNeededBookCount(); i++)
    {
        if (lib.bookIsAvailable(r.getNeededBook(i)))
        {
            availableBooksCount++;
            booksIndexes[j] = i;
            j++;
        }
    }

    r.setBooks(availableBooksCount);
    for (int i = 0; i < r.getAvailableBookCount(); i++)
    {
        r.setBook(i, lib.books[booksIndexes[i]]);
        lib.books[booksIndexes[i]].giveBook(r.getId());
    }
    delete[] booksIndexes;
}

void Library::initLibrary()
{
    int normalCount;
    std::cout << "Normal readers: ";
    std::cin >> normalCount;
    int greedyCount;
    std::cout << "Greedy readers: ";
    std::cin >> greedyCount;
    int carelessCount;
    std::cout << "Careless readers: ";
    std::cin >> carelessCount;

    normal = normalCount;
    greedy = greedyCount;
    careless = carelessCount;

    readerCount = normalCount + greedyCount + carelessCount;
    readers = new Reader *[readerCount];
    for (int i = 0; i < normalCount; i++)
    {
        readers[i] = new NormalReader(i);
        giveBooks(*readers[i], *this);
    }
    for (int i = normalCount; i < normalCount + greedyCount; i++)
    {
        readers[i] = new GreedyReader(i);
        giveBooks(*readers[i], *this);
    }
    for (int i = normalCount + greedyCount; i < readerCount; i++)
    {
        readers[i] = new CarelessReader(i);
        giveBooks(*readers[i], *this);
    }
}

bool Library::bookIsAvailable(int ind)
{
    return books[ind].isAvailable();
}

int Library::inBookCount()
{
    int count = 0;

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].isAvailable())
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
        if (books[i].isLost())
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
        if (books[i].isForgotten())
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
              << " Greedy readers: " << greedy << std::endl
              << " Careless readers: " << careless << std::endl
              << " Lost books list: " << std::endl;
    report << "Summary: " << std::endl
           << " Readers: " << readerCount << std::endl
           << " Lost books: " << lostBookCount() << std::endl
           << " Normal readers: " << normal << std::endl
           << " Greedy readers: " << greedy << std::endl
           << " Careless readers: " << careless << std::endl
           << " Lost books list: " << std::endl;

    for (int i = 0; i < readerCount; i++)
    {
        if (books[i].isLost())
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