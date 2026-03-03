#ifndef DAYABLE_H
#define DAYABLE_H

#include <fstream>

class Dayable
{
public:
    Dayable();
    virtual void day(std::ofstream &report);
};

#endif