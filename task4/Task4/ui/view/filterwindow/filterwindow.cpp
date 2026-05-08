#include "filterwindow.h"
#include "ui_filterwindow.h"
#include <QStringListModel>
#include <QMdiSubWindow>

FilterWindow::FilterWindow(FilterViewModel &viewModel, QMdiArea *mdiArea, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FilterWindow), viewModel(viewModel), mdiArea(mdiArea)
{
    ui->setupUi(this);

    this->viewModel.writeLog(Logger::Level::DEBUG, "Открыто окно фильтра");

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
        this->viewModel.writeLog(Logger::Level::INFO, "Включен предмет "+selectedText);
        updateSubjectDataLists(); });

    connect(ui->addExclude, &QPushButton::clicked, [=]()
            {
        string selectedText = ui->comboExclude->currentText().toStdString();
        this->viewModel.addToQuery(selectedText, true);
        this->viewModel.writeLog(Logger::Level::INFO, "Исключен предмет "+selectedText);
        updateSubjectDataLists(); });

    connect(ui->removeInclude, &QPushButton::clicked, [=]()
            {
        string selectedText = ui->includeList->currentIndex().data().toString().toStdString();
        this->viewModel.removeFromQuery(selectedText, false);
        this->viewModel.writeLog(Logger::Level::INFO, "Удален включенный предмет "+selectedText);
        updateSubjectDataLists(); });

    connect(ui->removeExclude, &QPushButton::clicked, [=]()
            {
        string selectedText = ui->excludeList->currentIndex().data().toString().toStdString();
        this->viewModel.removeFromQuery(selectedText, true);
        this->viewModel.writeLog(Logger::Level::INFO, "Удален исключенный предмет предмет "+selectedText);
        updateSubjectDataLists(); });

    this->viewModel.writeLog(Logger::Level::DEBUG, "Данные ui установлены");
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

    this->viewModel.writeLog(Logger::Level::DEBUG, "Обновлены данные исключенных предметов");
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

    this->viewModel.writeLog(Logger::Level::DEBUG, "Обновлены данные включенных предметов");
}

void FilterWindow::updateSubjectDataLists()
{
    this->viewModel.writeLog(Logger::Level::DEBUG, "Начато обновление предметов");

    updateExcludes();
    updateIncludes();
    ui->queryText->setText(QString::fromStdString(this->viewModel.getQueryText()));

    this->viewModel.writeLog(Logger::Level::DEBUG, "Завершено обновление предметов");
}

FilterViewModel &FilterWindow::getViewModel()
{
    return this->viewModel;
}

FilterWindow::~FilterWindow()
{
    delete ui;

    this->viewModel.writeLog(Logger::Level::DEBUG, "Окно фильтров закрыто");
}