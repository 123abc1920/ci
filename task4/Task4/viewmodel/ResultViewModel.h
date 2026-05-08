#pragma once

#include "Finder.h"
#include <memory>
#include "Logger.h"
#include "ILoggable.h"
#include <vector>
#include <string>

class ResultViewModel : public ILoggable
{
private:
    std::shared_ptr<Finder> finder;
    std::vector<std::string> result;

public:
    ResultViewModel(std::shared_ptr<Finder> finder, Logger &logger);
    ~ResultViewModel();

    std::vector<std::string> find();
    std::vector<std::string> getResult();
};