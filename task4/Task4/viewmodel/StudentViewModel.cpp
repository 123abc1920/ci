#include "StudentViewModel.h"

StudentViewModel::StudentViewModel(QStringListModel *model)
{
    this->model = model;
}

QStringListModel *StudentViewModel::getModel()
{
    return this->model;
}