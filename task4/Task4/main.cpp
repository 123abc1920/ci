#include <QApplication>
#include "ui/view/mainwindow/mainwindow.h"
#include "MainViewModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileReader fileReader;
    InMemoryRepository inMemoryRepository;

    Query query;

    MainViewModel mainViewModel(fileReader, inMemoryRepository, query);

    MainWindow w(mainViewModel);
    w.show();

    return a.exec();
}
