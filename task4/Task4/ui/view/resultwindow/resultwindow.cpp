#include "resultwindow.h"
#include "ui_resultwindow.h"
#include <iostream>
#include <set>
#include <string>
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>

using namespace std;

ResultWindow::ResultWindow(ResultViewModel &viewModel, Finder &finder, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ResultWindow), finder(finder), viewModel(viewModel)
{
    ui->setupUi(this);

    auto data = this->finder.find();
    QStringListModel *model = new QStringListModel(this);
    QStringList items;
    for (auto &row : data)
    {
        items << QString::fromStdString(row);
    }
    model->setStringList(items);
    ui->resultList->setModel(model);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}