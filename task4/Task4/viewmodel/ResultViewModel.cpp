#include "ResultViewModel.h"

ResultViewModel::ResultViewModel(std::shared_ptr<Finder> finder, Logger &logger)
    : ILoggable(logger), finder(std::move(finder))
{
}

vector<string> ResultViewModel::find()
{
    return this->finder->find();
}

ResultViewModel::~ResultViewModel()
{
}