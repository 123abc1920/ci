#include <QApplication>
#include "ui/view/mainwindow/mainwindow.h"
#include "MainViewModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileReader fileReader;
    InMemoryRepository inMemoryRepository;

    MainViewModel mainViewModel(fileReader, inMemoryRepository);

    MainWindow w(mainViewModel);
    w.show();

    return a.exec();
}
