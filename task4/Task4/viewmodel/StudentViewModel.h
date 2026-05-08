#pragma once

#include <QStringListModel>
#include "InMemoryRepository.h"
#include "SubjectsRepository.h"
#include "ILoggable.h"

class StudentViewModel : public ILoggable
{
private:
    QStringListModel *model;
    SubjectsRepository subjectsRepository;
    InMemoryRepository inMemoryRepository;

public:
    StudentViewModel(QStringListModel *model,
                     const SubjectsRepository &subjectsRepository,
                     const InMemoryRepository &inMemoryRepository,
                     Logger &logger);

    QStringListModel *getModel();
    SubjectsRepository &getSubjectsRepository();
    InMemoryRepository &getInMemoryRepository();
};
