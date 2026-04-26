#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <set>
#include <string>
#include <QDebug>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
            { openFile(); });
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Выберите файл"),
                                                    "",
                                                    tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));

    if (fileName.isEmpty())
    {
        qDebug() << "Файл не выбран";
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Не удалось открыть файл: " << file.errorString().toStdString();
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    qDebug() << content.toStdString();
}

MainWindow::~MainWindow()
{
    delete ui;
}
