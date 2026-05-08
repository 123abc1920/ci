#include "ResultViewModel.h"

ResultViewModel::ResultViewModel(std::shared_ptr<Finder> finder, Logger &logger)
    : ILoggable(logger), finder(std::move(finder))
{
}

vector<string> ResultViewModel::find()
{
    auto resultData = this->finder->find();
    this->result = resultData;

    return resultData;
}

vector<string> ResultViewModel::getResult()
{
    return this->result;
}

ResultViewModel::~ResultViewModel()
{
}