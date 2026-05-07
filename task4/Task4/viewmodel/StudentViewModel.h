#pragma once

#include <QStringListModel>
#include "InMemoryRepository.h"
#include "SubjectsRepository.h"

class StudentViewModel
{
private:
    QStringListModel *model;

    SubjectsRepository subjectsRepository;
    InMemoryRepository inMemoryRepository;

public:
    StudentViewModel(QStringListModel *model, SubjectsRepository &subjectsRepository, InMemoryRepository &inMemoryRepository);

    QStringListModel *getModel();
    SubjectsRepository &getSubjectsRepository();
    InMemoryRepository &getInMemoryRepository();
};