#include "StudentViewModel.h"

StudentViewModel::StudentViewModel(QStringListModel *model,
                                   const SubjectsRepository &subjectsRepository,
                                   const InMemoryRepository &inMemoryRepository,
                                   Logger &logger)
    : ILoggable(logger), model(model), subjectsRepository(subjectsRepository), inMemoryRepository(inMemoryRepository)
{
}

QStringListModel *StudentViewModel::getModel()
{
    return model;
}

SubjectsRepository &StudentViewModel::getSubjectsRepository()
{
    return subjectsRepository;
}

InMemoryRepository &StudentViewModel::getInMemoryRepository()
{
    return inMemoryRepository;
}
