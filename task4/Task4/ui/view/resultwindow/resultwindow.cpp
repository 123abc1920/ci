#include "resultwindow.h"
#include "ui_resultwindow.h"
#include <iostream>
#include <set>
#include <string>
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>

using namespace std;

ResultWindow::ResultWindow(ResultViewModel &viewModel, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ResultWindow), viewModel(viewModel)
{
    ui->setupUi(this);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}