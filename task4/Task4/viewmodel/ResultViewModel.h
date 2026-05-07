#pragma once

#include "Finder.h"
#include <memory>
#include "Logger.h"
#include "BaseViewModel.h"

class ResultViewModel : public BaseViewModel
{
private:
    std::shared_ptr<Finder> finder;

public:
    ResultViewModel(std::shared_ptr<Finder> finder, Logger &logger);
    ~ResultViewModel();

    vector<string> find();
};