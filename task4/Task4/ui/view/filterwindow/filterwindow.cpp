#include "filterwindow.h"
#include "ui_filterwindow.h"
#include <QStringListModel>
#include <QMdiSubWindow>

FilterWindow::FilterWindow(FilterViewModel &viewModel, QMdiArea *mdiArea, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FilterWindow), viewModel(viewModel), mdiArea(mdiArea)
{
    ui->setupUi(this);

    vector<string> subjects = this->viewModel.getSubjects();
    for (const auto &subject : subjects)
    {
        ui->comboInclude->addItem(QString::fromStdString(subject));
        ui->comboExclude->addItem(QString::fromStdString(subject));
    }

    connect(ui->addInclude, &QPushButton::clicked, [=]()
            {
        string selectedText = ui->comboInclude->currentText().toStdString();
        this->viewModel.addToQuery(selectedText, false);
        updateSubjectDataLists(); });

    connect(ui->addExclude, &QPushButton::clicked, [=]()
            {
        string selectedText = ui->comboExclude->currentText().toStdString();
        this->viewModel.addToQuery(selectedText, true);
        updateSubjectDataLists(); });

    connect(ui->removeInclude, &QPushButton::clicked, [=]()
            {
        string selectedText = ui->includeList->currentIndex().data().toString().toStdString();
        this->viewModel.removeFromQuery(selectedText, false);
        updateSubjectDataLists(); });

    connect(ui->removeExclude, &QPushButton::clicked, [=]()
            {
        string selectedText = ui->excludeList->currentIndex().data().toString().toStdString();
        this->viewModel.removeFromQuery(selectedText, true);
        updateSubjectDataLists(); });
}

void FilterWindow::updateExcludes()
{
    QStringListModel *model = new QStringListModel(this);
    QStringList items;
    for (auto &subject : this->viewModel.getQueryData(true))
    {
        items << QString::fromStdString(subject);
    }
    model->setStringList(items);
    ui->excludeList->setModel(model);
}

void FilterWindow::updateIncludes()
{
    QStringListModel *model = new QStringListModel(this);
    QStringList items;
    for (auto &subject : this->viewModel.getQueryData(false))
    {
        items << QString::fromStdString(subject);
    }
    model->setStringList(items);
    ui->includeList->setModel(model);
}

void FilterWindow::updateSubjectDataLists()
{
    updateExcludes();
    updateIncludes();
    ui->queryText->setText(QString::fromStdString(this->viewModel.getQueryText()));
}

FilterWindow::~FilterWindow()
{
    delete ui;
}