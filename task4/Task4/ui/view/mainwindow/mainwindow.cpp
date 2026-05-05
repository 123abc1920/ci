#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MainViewModel.h"
#include <QStringListModel>
#include <QIODevice>
#include <QFileDialog>
#include <QFile>
#include "StudentViewModel.h"
#include "FilterViewModel.h"
#include <QMdiSubWindow>
#include "studentwindow.h"
#include "filterwindow.h"
#include "ResultViewModel.h"
#include "resultwindow.h"

MainWindow::MainWindow(MainViewModel &viewModel, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), viewModel(viewModel)
{
    ui->setupUi(this);

    this->viewModel = viewModel;

    connect(ui->openFile, &QAction::triggered, this, [this]()
            {
    auto fileContent = openFile();
    if (!fileContent.empty()) {
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

        StudentViewModel *viewModel = new StudentViewModel(model);
        StudentWindow *studentWin = new StudentWindow(*viewModel, this);
        QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(studentWin);
        subWindow->setWindowTitle("Список студентов");
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show();
    } });

    connect(ui->filterBtn, &QAction::triggered, this, [this]()
            {
        FilterViewModel *viewModel = new FilterViewModel();
        FilterWindow *filterWin = new FilterWindow(*viewModel, ui->mdiArea, this);
        QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(filterWin);
        subWindow->setWindowTitle("Фильтры");
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show(); });

    connect(ui->searchBtn, &QAction::triggered, this, [this]()
            {
        ResultViewModel *vm = new ResultViewModel();
        ResultWindow *win = new ResultWindow(*vm, this);
        QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(win);
        subWindow->setWindowTitle("Результаты");
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show(); });
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