#include "mainwindow.h"
#include "ui_mainwindow.h"
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

MainWindow::~MainWindow()
{
    delete ui;
}
