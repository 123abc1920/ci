#include "filterwindow.h"
#include "ui_filterwindow.h"
#include <QStringListModel>
#include <QMdiSubWindow>

FilterWindow::FilterWindow(FilterViewModel *viewModel, QMdiArea *mdiArea, QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::FilterWindow>()),
      viewModel(viewModel), mdiArea(mdiArea)
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

    connect(ui->addInclude, &QPushButton::clicked, [this]()
            {
        if (!this->viewModel) return;
        std::string selectedText = ui->comboInclude->currentText().toStdString();
        this->viewModel->addToQuery(selectedText, false);
        updateSubjectDataLists(); });

    connect(ui->addExclude, &QPushButton::clicked, [this]()
            {
        if (!this->viewModel) return;
        std::string selectedText = ui->comboExclude->currentText().toStdString();
        this->viewModel->addToQuery(selectedText, true);
        updateSubjectDataLists(); });
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
        viewModel->writeLog(Logger::Level::DEBUG, "Окно фильтров закрыто");
    }
}
