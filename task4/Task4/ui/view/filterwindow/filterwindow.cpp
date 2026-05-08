#include "filterwindow.h"
#include "ui_filterwindow.h"
#include <QStringListModel>

FilterWindow::FilterWindow(FilterViewModel *viewModel, QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::FilterWindow>()),
      viewModel(viewModel)
{
    ui->setupUi(this);

    if (this->viewModel)
    {
        this->viewModel->writeLog(Logger::Level::DEBUG, "Открыто окно фильтра");

        const auto &subjects = this->viewModel->getSubjects();
        for (const auto &subject : subjects)
        {
            ui->comboInclude->addItem(QString::fromStdString(subject));
            ui->comboExclude->addItem(QString::fromStdString(subject));
        }
    }

    connect(ui->addInclude, &QPushButton::clicked, this, &FilterWindow::onAddIncludeClicked);
    connect(ui->addExclude, &QPushButton::clicked, this, &FilterWindow::onAddExcludeClicked);
    connect(ui->removeInclude, &QPushButton::clicked, this, &FilterWindow::onRemoveIncludeClicked);
    connect(ui->removeExclude, &QPushButton::clicked, this, &FilterWindow::onRemoveExcludeClicked);
}

void FilterWindow::onAddIncludeClicked()
{
    if (!viewModel)
        return;
    auto selectedText = ui->comboInclude->currentText().toStdString();
    viewModel->addToQuery(selectedText, false);
    viewModel->writeLog(Logger::Level::INFO, "Удален предмет: " + selectedText);
    updateSubjectDataLists();
}

void FilterWindow::onAddExcludeClicked()
{
    if (!viewModel)
        return;
    auto selectedText = ui->comboExclude->currentText().toStdString();
    viewModel->addToQuery(selectedText, true);
    viewModel->writeLog(Logger::Level::INFO, "Включен предмет: " + selectedText);
    updateSubjectDataLists();
}

void FilterWindow::onRemoveIncludeClicked()
{
    if (!viewModel)
        return;
    auto currentIdx = ui->includeList->currentIndex();
    if (!currentIdx.isValid())
        return;

    auto selectedText = currentIdx.data().toString().toStdString();
    viewModel->removeFromQuery(selectedText, false);
    viewModel->writeLog(Logger::Level::INFO, "Удален включенный предмет: " + selectedText);
    updateSubjectDataLists();
}

void FilterWindow::onRemoveExcludeClicked()
{
    if (!viewModel)
        return;
    auto currentIdx = ui->excludeList->currentIndex();
    if (!currentIdx.isValid())
        return;

    auto selectedText = currentIdx.data().toString().toStdString();
    viewModel->removeFromQuery(selectedText, true);
    viewModel->writeLog(Logger::Level::INFO, "Удален исключенный предмет: " + selectedText);
    updateSubjectDataLists();
}

void FilterWindow::updateExcludes()
{
    if (!viewModel)
        return;
    auto *model = new QStringListModel(this);
    QStringList items;
    for (const auto &subject : viewModel->getQueryData(true))
    {
        items << QString::fromStdString(subject);
    }
    model->setStringList(items);

    auto *oldModel = ui->excludeList->model();
    ui->excludeList->setModel(model);
    if (oldModel)
        oldModel->deleteLater();
}

void FilterWindow::updateIncludes()
{
    if (!viewModel)
        return;
    auto *model = new QStringListModel(this);
    QStringList items;
    for (const auto &subject : viewModel->getQueryData(false))
    {
        items << QString::fromStdString(subject);
    }
    model->setStringList(items);

    auto *oldModel = ui->includeList->model();
    ui->includeList->setModel(model);
    if (oldModel)
        oldModel->deleteLater();
}

void FilterWindow::updateSubjectDataLists()
{
    if (!viewModel)
        return;
    updateExcludes();
    updateIncludes();
    ui->queryText->setText(QString::fromStdString(viewModel->getQueryText()));
}

FilterViewModel *FilterWindow::getViewModel() const
{
    return viewModel;
}

FilterWindow::~FilterWindow()
{
    if (viewModel)
    {
        viewModel->writeLog(Logger::Level::INFO, "Окно фильтров закрыто");
    }
}
