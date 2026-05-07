#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(StudentViewModel &viewModel, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::StudentWindow), viewModel(viewModel)
{
    ui->setupUi(this);

    this->viewModel.writeLog(Logger::Level::DEBUG, "Открыто окно студентов");

    this->viewModel = viewModel;

    ui->studentList->setModel(viewModel.getModel());

    this->viewModel.writeLog(Logger::Level::DEBUG, "Установлен список студентов в ui");
}

StudentViewModel &StudentWindow::getViewModel()
{
    return this->viewModel;
}

StudentWindow::~StudentWindow()
{
    delete ui;

    this->viewModel.writeLog(Logger::Level::DEBUG, "Окно студентов закрыто");
}