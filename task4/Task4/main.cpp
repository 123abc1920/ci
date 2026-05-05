#include <QApplication>
#include "ui/view/mainwindow/mainwindow.h"
#include "MainViewModel.h"
#include "SubjectsRepository.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileReader fileReader;
    InMemoryRepository inMemoryRepository;
    SubjectsRepository subjectsRepository;

    Query query;

    MainViewModel mainViewModel(fileReader, inMemoryRepository, query, subjectsRepository);
    MainWindow w(mainViewModel);
    w.show();

    return a.exec();
}
