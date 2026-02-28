#ifndef CARELESS_READER_H
#define CARELESS_READER_H

#include "Reader.h"

class CarelessReader : public Reader
{
public:
    CarelessReader(int _id);

    void day(std::ofstream &report);
};

#endif