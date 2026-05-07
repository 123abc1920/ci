#pragma once

#include "Finder.h"
#include <memory>

class ResultViewModel
{
private:
    std::shared_ptr<Finder> finder;

public:
    ResultViewModel(std::shared_ptr<Finder> finder);
    ~ResultViewModel();

    vector<string> find();
};