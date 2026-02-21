// 9 номер
#include <iostream>

class Reader
{
public:
    int id;
    int *books;
    int *neededBooks;

    Reader() {}

    Reader(int _id)
    {
        id = _id;

        int bookCount = 1 + rand() % 5;
        neededBooks = new int[bookCount];
        for (int i = 0; i < bookCount; i++)
        {
            neededBooks[i] = 1 + rand() % 30;
        }
    }

    void setBooks(int bookCount)
    {
        books = new int[bookCount];
    }

    void releaseReader()
    {
        delete[] neededBooks;
        delete[] books;
    }
};

class NormalReader : Reader
{
    NormalReader(int _id)
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

class CarelessReader : Reader
{
    CarelessReader(int _id)
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

class GreadyReader : Reader
{
    GreadyReader(int _id)
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

class Book
{
public:
    int id;
    int time;

    Book(int _id)
    {
        id = _id;

        time = 3 + rand() % 30;
    }
};

class Library
{
public:
    int *books;

    Library()
    {
        int booksCount = 40 + rand() % 80;
        books = new int[booksCount];
    }

    void releaseBooks()
    {
        delete[] books;
    }
};

int main()
{
    return 0;
}