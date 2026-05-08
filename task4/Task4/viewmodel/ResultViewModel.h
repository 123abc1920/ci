#pragma once

#include "Finder.h"
#include <memory>
#include <vector>
#include <string>
#include "ILoggable.h"

class ResultViewModel : public ILoggable
{
private:
    std::shared_ptr<Finder> finder;
    std::vector<std::string> result;

public:
    explicit ResultViewModel(std::shared_ptr<Finder> finder, Logger &logger);
    ~ResultViewModel() override = default;

    const std::vector<std::string> &find();

    const std::vector<std::string> &getResult() const;
};
