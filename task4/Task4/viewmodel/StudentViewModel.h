#pragma once

#include <QStringListModel>
#include "InMemoryRepository.h"
#include "SubjectsRepository.h"
#include "BaseViewModel.h"
#include "Logger.h"

class StudentViewModel : public BaseViewModel
{
private:
    QStringListModel *model;

    SubjectsRepository subjectsRepository;
    InMemoryRepository inMemoryRepository;

public:
    StudentViewModel(QStringListModel *model, SubjectsRepository &subjectsRepository, InMemoryRepository &inMemoryRepository, Logger &logger);

    QStringListModel *getModel();
    SubjectsRepository &getSubjectsRepository();
    InMemoryRepository &getInMemoryRepository();
};