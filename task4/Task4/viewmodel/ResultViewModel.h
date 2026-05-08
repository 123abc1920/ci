#pragma once

#include "Finder.h"
#include <memory>
#include "Logger.h"
#include "ILoggable.h"

class ResultViewModel : public ILoggable
{
private:
    std::shared_ptr<Finder> finder;
    vector<string> result;

public:
    ResultViewModel(std::shared_ptr<Finder> finder, Logger &logger);
    ~ResultViewModel();

    vector<string> find();
    vector<string> getResult();
};