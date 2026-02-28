#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <iostream>
#include <fstream>

class Printable
{
public:
    Printable();
    virtual ~Printable() {}
    virtual void print(std::ofstream& report);
};

#endif