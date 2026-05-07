#include <QApplication>
#include "ui/view/mainwindow/mainwindow.h"
#include "MainViewModel.h"
#include "FileReader.h"
#include "Saver.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileReader fileReader;
    Saver saver;
    Logger logger;

    MainViewModel mainViewModel(fileReader, saver);
    MainWindow w(mainViewModel);
    w.show();

    return a.exec();
}
