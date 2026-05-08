#include <QApplication>
#include "ui/view/mainwindow/mainwindow.h"
#include "MainViewModel.h"
#include "FileReader.h"
#include "Saver.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger logger;
    FileReader fileReader(logger);
    Saver saver(logger);

    MainViewModel mainViewModel(fileReader, saver, logger);
    MainWindow w(mainViewModel, logger);
    w.show();

    return a.exec();
}
