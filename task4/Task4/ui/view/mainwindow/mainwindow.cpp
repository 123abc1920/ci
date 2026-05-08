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
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()), viewModel(viewModel), logger(logger)
{
    ui->setupUi(this);
    viewModel.writeLog(Logger::Level::INFO, "Сеанс начат");

    connect(ui->openFile, &QAction::triggered, this, &MainWindow::onOpenFileTriggered);
    connect(ui->filterBtn, &QAction::triggered, this, &MainWindow::onFilterBtnTriggered);
    connect(ui->searchBtn, &QAction::triggered, this, &MainWindow::onSearchBtnTriggered);
    connect(ui->saveBtn, &QAction::triggered, this, &MainWindow::onSaveBtnTriggered);
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::updateMenuItems);
}

void MainWindow::onOpenFileTriggered()
{
    viewModel.writeLog(Logger::Level::INFO, "Пользователь открывает файл");

    std::string fileContent = openFile();
    if (fileContent.empty())
    {
        viewModel.writeLog(Logger::Level::WARNING, "Данные для загрузки не найдены");
        return;
    }

    auto inMemoryRepository = viewModel.readDB(fileContent);
    auto subjectsRepository = viewModel.readSubjects(fileContent);

    auto *model = new QStringListModel(this);
    QStringList items;

    for (const auto &[index, student] : inMemoryRepository.getAll())
    {
        QString text = QString("%1 |    %2    | %3")
                           .arg(index)
                           .arg(QString::fromStdString(student.getName()))
                           .arg(QString::fromStdString(student.getSubjects()));
        items << text;
    }
    model->setStringList(items);

    auto *studentVm = new StudentViewModel(model, subjectsRepository, inMemoryRepository, logger);
    auto *studentWin = new StudentWindow(studentVm, this);

    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(studentWin);

    subWindow->setWindowTitle("Список студентов");
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();

    viewModel.writeLog(Logger::Level::INFO, "Данные загружены");
}

void MainWindow::onFilterBtnTriggered()
{
    viewModel.writeLog(Logger::Level::INFO, "Начата фильтрация");

    auto *activeSubWin = ui->mdiArea->activeSubWindow();
    if (!activeSubWin)
    {
        viewModel.writeLog(Logger::Level::ERROR, "Ошибка: никакое окно не выбрано");
        return;
    }

    if (auto *studentWin = qobject_cast<StudentWindow *>(activeSubWin->widget()))
    {
        auto *vm = studentWin->getViewModel();

        auto *filterVm = new FilterViewModel(vm->getSubjectsRepository(), vm->getInMemoryRepository(), logger);
        auto *filterWin = new FilterWindow(filterVm, this);

        auto *subWindow = ui->mdiArea->addSubWindow(filterWin);

        subWindow->setWindowTitle("Фильтры");
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show();

        viewModel.writeLog(Logger::Level::INFO, "Открыто окно фильтрации");
    }
    else
    {
        viewModel.writeLog(Logger::Level::ERROR, "Ошибка: выбрано не то окно");
    }
}

void MainWindow::onSearchBtnTriggered()
{
    viewModel.writeLog(Logger::Level::INFO, "Начат поиск");

    auto *activeSubWin = ui->mdiArea->activeSubWindow();
    if (!activeSubWin)
    {
        viewModel.writeLog(Logger::Level::ERROR, "Ошибка: никакое окно не выбрано");
        return;
    }

    if (auto *filterWin = qobject_cast<FilterWindow *>(activeSubWin->widget()))
    {
        auto *filterVm = filterWin->getViewModel();

        auto finder = std::make_shared<Finder>(filterVm->getQuery(), filterVm->getInMemoryRepository(), logger);

        auto *resultVm = new ResultViewModel(finder, logger);
        auto *resultWin = new ResultWindow(resultVm, this);

        auto *subWindow = ui->mdiArea->addSubWindow(resultWin);

        subWindow->setWindowTitle("Результаты");
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show();
    }
    else
    {
        viewModel.writeLog(Logger::Level::ERROR, "Ошибка: выбрано не то окно");
    }
}

void MainWindow::onSaveBtnTriggered()
{
    viewModel.writeLog(Logger::Level::INFO, "Начато сохранение");

    auto *activeSubWin = ui->mdiArea->activeSubWindow();
    if (!activeSubWin)
    {
        viewModel.writeLog(Logger::Level::ERROR, "Ошибка: никакое окно не выбрано");
        return;
    }

    if (auto *resultWin = qobject_cast<ResultWindow *>(activeSubWin->widget()))
    {
        auto *vm = resultWin->getViewModel();
        auto data = vm->getResult();

        QString filePath = QFileDialog::getSaveFileName(this, tr("Экспорт данных"), "", tr("Текстовые файлы (*.txt)"));

        if (filePath.isEmpty())
        {
            viewModel.writeLog(Logger::Level::ERROR, "Ошибка: файл не выбран");
            return;
        }

        if (viewModel.save(data, filePath.toStdString()))
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
        viewModel.writeLog(Logger::Level::ERROR, "Ошибка: выбрано не то окно");
    }
}

std::string MainWindow::openFile()
{
    viewModel.writeLog(Logger::Level::DEBUG, "Открыт диалог выбора файла");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));

    if (fileName.isEmpty())
    {
        viewModel.writeLog(Logger::Level::WARNING, "Файл не выбран");
        return {};
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        viewModel.writeLog(Logger::Level::ERROR, "Не удалось открыть файл: " + file.errorString().toStdString());
        return {};
    }

    QTextStream in(&file);
    QString content = in.readAll();

    viewModel.writeLog(Logger::Level::DEBUG, "Файл прочитан: " + fileName.toStdString());
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
    this->viewModel.writeLog(Logger::Level::INFO, "Сеанс завершен");
}