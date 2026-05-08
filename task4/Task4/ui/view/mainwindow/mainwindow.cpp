#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MainViewModel.h"
#include <QStringListModel>
#include <QIODevice>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include "StudentViewModel.h"
#include "FilterViewModel.h"
#include <QMdiSubWindow>
#include "studentwindow.h"
#include "filterwindow.h"
#include "ResultViewModel.h"
#include "resultwindow.h"
#include <QMessageBox>
#include "Logger.h"

MainWindow::MainWindow(MainViewModel &viewModel, Logger &logger, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), viewModel(viewModel), logger(logger)
{
    ui->setupUi(this);

    this->viewModel.writeLog(Logger::Level::INFO, "Сеанс начат");
    this->viewModel.writeLog(Logger::Level::DEBUG, "Логи пишутся в build/logs.txt");

    connect(ui->openFile, &QAction::triggered, this, &MainWindow::onOpenFileTriggered);
    connect(ui->filterBtn, &QAction::triggered, this, &MainWindow::onFilterBtnTriggered);
    connect(ui->searchBtn, &QAction::triggered, this, &MainWindow::onSearchBtnTriggered);
    connect(ui->saveBtn, &QAction::triggered, this, &MainWindow::onSaveBtnTriggered);

    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::updateMenuItems);

    this->updateMenuItems(nullptr);
    this->viewModel.writeLog(Logger::Level::DEBUG, "Подключены события ui");
}

void MainWindow::onOpenFileTriggered()
{
    this->viewModel.writeLog(Logger::Level::INFO, "Пользователь открывает файл");
    auto fileContent = openFile();
    if (!fileContent.empty())
    {
        InMemoryRepository inMemoryRepository = this->viewModel.readDB(fileContent);
        SubjectsRepository subjectsRepository = this->viewModel.readSubjects(fileContent);

        QStringListModel *model = new QStringListModel(this);
        QStringList items;

        for (auto &[index, student] : inMemoryRepository.getAll())
        {
            QString text = QString::number(index) + "|    " +
                           QString::fromStdString(student.getName()) +
                           "    |" + QString::fromStdString(student.getSubjects());
            items << text;
        }

        model->setStringList(items);

        StudentViewModel *viewModel = new StudentViewModel(model, subjectsRepository, inMemoryRepository, this->logger);
        StudentWindow *studentWin = new StudentWindow(*viewModel, this);
        QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(studentWin);
        subWindow->setWindowTitle("Список студентов");
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show();

        this->viewModel.writeLog(Logger::Level::INFO, "Данные загружены");
    }
    else
    {
        this->viewModel.writeLog(Logger::Level::WARNING, "Данные для загрузки не найдены");
    }
}

void MainWindow::onFilterBtnTriggered()
{
    this->viewModel.writeLog(Logger::Level::INFO, "Начата фильтрация");
    QMdiSubWindow *activeWindow = ui->mdiArea->activeSubWindow();
    if (activeWindow)
    {
        StudentWindow *studentWin = qobject_cast<StudentWindow *>(activeWindow->widget());
        if (studentWin)
        {
            StudentViewModel &vm = studentWin->getViewModel();
            FilterViewModel *viewModel = new FilterViewModel(vm.getSubjectsRepository(), vm.getInMemoryRepository(), this->logger);
            FilterWindow *filterWin = new FilterWindow(*viewModel, ui->mdiArea, this);
            QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(filterWin);
            subWindow->setWindowTitle("Фильтры");
            subWindow->setAttribute(Qt::WA_DeleteOnClose);
            subWindow->show();

            this->viewModel.writeLog(Logger::Level::INFO, "Открыто окно фильтрации");
        }
        else
        {
            this->viewModel.writeLog(Logger::Level::ERROR, "Ошибка: выбрано не то окно");
        }
    }
    else
    {
        this->viewModel.writeLog(Logger::Level::ERROR, "Ошибка: никакое окно не выбрано");
    }
}

void MainWindow::onSearchBtnTriggered()
{
    this->viewModel.writeLog(Logger::Level::INFO, "Начат поиск");
    QMdiSubWindow *activeWindow = ui->mdiArea->activeSubWindow();
    if (activeWindow)
    {
        FilterWindow *filterWin = qobject_cast<FilterWindow *>(activeWindow->widget());
        if (filterWin)
        {
            FilterViewModel &filtervm = filterWin->getViewModel();
            auto finder = make_shared<Finder>(filtervm.getQuery(), filtervm.getInMemoryRepository(), this->logger);
            ResultViewModel *vm = new ResultViewModel(finder, this->logger);
            ResultWindow *win = new ResultWindow(*vm, this);
            QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(win);
            subWindow->setWindowTitle("Результаты");
            subWindow->setAttribute(Qt::WA_DeleteOnClose);
            subWindow->show();
        }
        else
        {
            this->viewModel.writeLog(Logger::Level::ERROR, "Ошибка: выбрано не то окно");
        }
    }
    else
    {
        this->viewModel.writeLog(Logger::Level::ERROR, "Ошибка: никакое окно не выбрано");
    }
}

void MainWindow::onSaveBtnTriggered()
{
    this->viewModel.writeLog(Logger::Level::INFO, "Начато сохранение");
    QMdiSubWindow *activeWindow = ui->mdiArea->activeSubWindow();
    if (activeWindow)
    {
        ResultWindow *resultWin = qobject_cast<ResultWindow *>(activeWindow->widget());
        if (resultWin)
        {
            ResultViewModel &vm = resultWin->getViewModel();
            auto data = vm.getResult();

            QString filePath = QFileDialog::getSaveFileName(this,
                                                            tr("Экспорт данных"),
                                                            "",
                                                            tr("Текстовые файлы (*.txt);;"));

            if (filePath.isEmpty())
            {
                this->viewModel.writeLog(Logger::Level::ERROR, "Ошибка: файл не выбран");
                return;
            }

            bool result = this->viewModel.save(data, filePath.toStdString());

            if (result)
            {
                QMessageBox::information(this, tr("Успех"), tr("Данные успешно экспортированы!"));
            }
            else
            {
                QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось экспортировать данные."));
            }
        }
        else
        {
            this->viewModel.writeLog(Logger::Level::ERROR, "Ошибка: выбрано не то окно");
        }
    }
    else
    {
        this->viewModel.writeLog(Logger::Level::ERROR, "Ошибка: никакое окно не выбрано");
    }
}

string MainWindow::openFile()
{
    this->viewModel.writeLog(Logger::Level::DEBUG, "Открыт диалог выбора файла");

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Выберите файл"),
                                                    "",
                                                    tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));

    if (fileName.isEmpty())
    {
        this->viewModel.writeLog(Logger::Level::WARNING, "Файл не выбран");
        return "";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->viewModel.writeLog(Logger::Level::ERROR, "Не удалось открыть файл: " + file.errorString().toStdString());
        return "";
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    this->viewModel.writeLog(Logger::Level::DEBUG, "Файл был выбран: " + fileName.toStdString());
    return content.toStdString();
}

void MainWindow::updateMenuItems(QMdiSubWindow *activeWindow)
{
    this->viewModel.writeLog(Logger::Level::DEBUG, "Обновлены кнопки меню");

    ui->openFile->setEnabled(true);
    ui->filterBtn->setEnabled(false);
    ui->saveBtn->setEnabled(false);
    ui->searchBtn->setEnabled(false);

    if (!activeWindow)
    {
        this->viewModel.writeLog(Logger::Level::WARNING, "Никакое окно не активно");
        return;
    }

    QWidget *content = activeWindow->widget();
    QString className = content->metaObject()->className();

    if (className == "StudentWindow")
    {
        ui->filterBtn->setEnabled(true);
    }
    if (className == "FilterWindow")
    {
        ui->searchBtn->setEnabled(true);
    }
    if (className == "ResultWindow")
    {
        ui->saveBtn->setEnabled(true);
    }

    this->viewModel.writeLog(Logger::Level::DEBUG, "Меню обновлено, активно окно " + className.toStdString());
}

MainWindow::~MainWindow()
{
    delete ui;

    this->viewModel.writeLog(Logger::Level::INFO, "Сеанс завершен");
}