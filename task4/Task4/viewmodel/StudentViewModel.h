#pragma once

#include <QStringListModel>

class StudentViewModel
{
private:
    QStringListModel *model;

public:
    StudentViewModel(QStringListModel *model);

    QStringListModel *getModel();
};