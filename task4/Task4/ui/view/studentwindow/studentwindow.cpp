#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(StudentViewModel *viewModel, QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::StudentWindow>()),
      viewModel(viewModel)
{
    ui->setupUi(this);

    if (viewModel)
    {
        viewModel->writeLog(Logger::Level::DEBUG, "Открыто окно студентов");
        
        ui->studentList->setModel(viewModel->getModel());

        viewModel->writeLog(Logger::Level::DEBUG, "Установлен список студентов в ui");
    }
}

StudentViewModel *StudentWindow::getViewModel() const
{
    return viewModel;
}

StudentWindow::~StudentWindow()
{
    if (viewModel)
    {
        viewModel->writeLog(Logger::Level::DEBUG, "Окно студентов закрыто");
    }
}
