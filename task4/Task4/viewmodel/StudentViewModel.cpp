#include "StudentViewModel.h"

StudentViewModel::StudentViewModel(QStringListModel *model, SubjectsRepository &subjectsRepository, InMemoryRepository &inMemoryRepository, Logger &logger) : ILoggable(logger)
{
    this->model = model;
    this->inMemoryRepository = inMemoryRepository;
    this->subjectsRepository = subjectsRepository;
}

QStringListModel *StudentViewModel::getModel()
{
    return this->model;
}

SubjectsRepository &StudentViewModel::getSubjectsRepository()
{
    return this->subjectsRepository;
}

InMemoryRepository &StudentViewModel::getInMemoryRepository()
{
    return this->inMemoryRepository;
}