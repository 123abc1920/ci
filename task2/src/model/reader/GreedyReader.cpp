#include "GreedyReader.h"

GreedyReader::GreedyReader(int _id) : Reader(_id)
{
    id = _id;

    neededBooksCount = 5 + rand() % 10;
    neededBooks = new int[neededBooksCount];
    for (int i = 0; i < neededBooksCount; i++)
    {
        neededBooks[i] = 1 + rand() % 30;
    }
}