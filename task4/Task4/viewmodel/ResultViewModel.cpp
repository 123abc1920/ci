#include "ResultViewModel.h"

ResultViewModel::ResultViewModel(std::shared_ptr<Finder> finder, Logger &logger)
    : ILoggable(logger), finder(std::move(finder))
{
}

const std::vector<std::string> &ResultViewModel::find()
{
    if (finder)
    {
        result = finder->find();
    }

    return result;
}

const std::vector<std::string> &ResultViewModel::getResult() const
{
    return result;
}
