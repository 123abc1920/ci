#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultwindow.h"
#include <iostream>
#include <set>
#include <string>
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow(MainViewModel &viewModel, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), viewModel(viewModel)
{
    ui->setupUi(this);

    this->viewModel = viewModel;

    std::vector<QString> subjects = {"Математика", "Физика", "Биология", "Химия"};
    for (const auto &subject : subjects)
    {
        ui->includeComboBox->addItem(subject);
    }
    for (const auto &subject : subjects)
    {
        ui->excludeComboBox->addItem(subject);
    }

    connect(ui->openFileBtn, &QPushButton::clicked, [=]()
            { auto fileContent = openFile();
                this->viewModel.readDB(fileContent);
            
            QStringListModel* model = new QStringListModel(this);
            QStringList items;

            for (auto& [index, student] : this->viewModel.getAllStudents()) {
                QString text = QString::number(index) + "|    " + 
                            QString::fromStdString(student.getName()) + 
                            "    |" + QString::fromStdString(student.getSubjects());
                
                items << text;
            }

            model->setStringList(items);
            ui->dataList->setModel(model); });

    connect(ui->addIncludeSubjectBtn, &QPushButton::clicked, [=]()
            {
                string selectedText = ui->includeComboBox->currentText().toStdString();
                this->viewModel.addToQuery(selectedText, false);
                ui->searchQuery->setText(QString::fromStdString(this->viewModel.getQueryText()));
                updateSubjectDataLists(); });

    connect(ui->addExcludeSubjectBtn, &QPushButton::clicked, [=]()
            {
                string selectedText = ui->excludeComboBox->currentText().toStdString();
                this->viewModel.addToQuery(selectedText, true);
                ui->searchQuery->setText(QString::fromStdString(this->viewModel.getQueryText()));
                updateSubjectDataLists(); });

    connect(ui->removeIncludeSubjectBtn, &QPushButton::clicked, [=]()
            {
                string selectedText = ui->includeSubjectList->currentIndex().data().toString().toStdString();
                this->viewModel.removeFromQuery(selectedText, false);
                updateSubjectDataLists(); });

    connect(ui->removeExcludeSubjectBtn, &QPushButton::clicked, [=]()
            {
                string selectedText = ui->excludeSubjectList->currentIndex().data().toString().toStdString();
                this->viewModel.removeFromQuery(selectedText, true);
                updateSubjectDataLists(); });

    connect(ui->searchBtn, &QPushButton::clicked, [=]()
            {
                ResultViewModel* viewModel = new ResultViewModel();
                ResultWindow* window = new ResultWindow(*viewModel, this);
                window->setAttribute(Qt::WA_DeleteOnClose);
                window->show();
            });
}

string MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Выберите файл"),
                                                    "",
                                                    tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));

    if (fileName.isEmpty())
    {
        qDebug() << "Файл не выбран";
        return "";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Не удалось открыть файл: " << file.errorString().toStdString();
        return "";
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    return content.toStdString();
}

void MainWindow::updateExcludes()
{
    QStringListModel *model = new QStringListModel(this);
    QStringList items;

    for (auto &subject : this->viewModel.getQueryData(true))
    {
        items << QString::fromStdString(subject);
    }

    model->setStringList(items);
    ui->excludeSubjectList->setModel(model);
}

void MainWindow::updateIncludes()
{
    QStringListModel *model = new QStringListModel(this);
    QStringList items;

    for (auto &subject : this->viewModel.getQueryData(false))
    {
        items << QString::fromStdString(subject);
    }

    model->setStringList(items);
    ui->includeSubjectList->setModel(model);
}

void MainWindow::updateSubjectDataLists()
{
    updateExcludes();
    updateIncludes();
}

MainWindow::~MainWindow()
{
    delete ui;
}
