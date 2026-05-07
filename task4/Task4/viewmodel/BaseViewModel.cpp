#include "BaseViewModel.h"

BaseViewModel::BaseViewModel(Logger &logger) : logger(logger) {}

void BaseViewModel::writeLog(const Logger::Level &level, const string &message)
{
    this->logger->write(level, message);
}