#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(StudentViewModel &viewModel, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::StudentWindow), viewModel(viewModel)
{
    ui->setupUi(this);

    this->viewModel = viewModel;

    ui->studentList->setModel(viewModel.getModel());
}

StudentWindow::~StudentWindow()
{
    delete ui;
}