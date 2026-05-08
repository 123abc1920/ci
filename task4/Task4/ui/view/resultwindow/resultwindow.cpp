#include "resultwindow.h"
#include "ui_resultwindow.h"
#include <QStringListModel>

ResultWindow::ResultWindow(ResultViewModel *viewModel, QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::ResultWindow>()), viewModel(viewModel)
{
    ui->setupUi(this);

    if (this->viewModel)
    {
        this->viewModel->writeLog(Logger::Level::DEBUG, "Открыто окно результатов");

        const auto &data = this->viewModel->find();

        auto *model = new QStringListModel(this);
        QStringList items;
        for (const auto &row : data)
        {
            items << QString::fromStdString(row);
        }
        model->setStringList(items);
        ui->resultList->setModel(model);

        this->viewModel->writeLog(Logger::Level::DEBUG, "Установлены данные в ui результата");
    }
}

ResultViewModel *ResultWindow::getViewModel() const
{
    return viewModel;
}

ResultWindow::~ResultWindow()
{
    if (viewModel)
    {
        viewModel->writeLog(Logger::Level::INFO, "Окно результатов закрыто");
    }
}
