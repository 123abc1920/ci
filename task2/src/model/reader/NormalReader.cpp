#include "NormalReader.h"

NormalReader::NormalReader(int _id) : Reader(_id)
{
    id = _id;
    neededBooksCount = 1 + rand() % 5;
    neededBooks = new int[neededBooksCount];
    for (int i = 0; i < neededBooksCount; i++)
    {
        neededBooks[i] = 1 + rand() % 30;
    }
}