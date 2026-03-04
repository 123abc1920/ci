#include "CarelessReader.h"

CarelessReader::CarelessReader(int _id) : Reader(_id)
{
    id = _id;

    neededBooksCount = 1 + rand() % 5;
    neededBooks = new int[neededBooksCount];
    for (int i = 0; i < neededBooksCount; i++)
    {
        neededBooks[i] = 1 + rand() % 30;
    }
}

void CarelessReader::day(std::ofstream &report)
{
    for (int i = 0; i < availableBooksCount; i++)
    {
        int loseBook = 0 + rand() % LOSING_PROBABILITY;
        if (books[i]->isAvailable() == false && books[i]->getReaderId() == this->id)
        {
            if (books[i]->getTimeUntilend() <= 0)
            {
                int returnOrNot = 0 + rand() % 10;
                if (returnOrNot < 2)
                {
                    if (loseBook < LOST_NUMBER)
                    {
                        books[i]->setAvailable(false);
                        books[i]->setReaderId(-1);
                    }
                    else
                    {
                        books[i]->returnBook();
                    }
                }
            }
            if (books[i]->getReaderId() == this->id)
            {
                books[i]->bookDay();
            }
        }
    }
    this->print(report);
}