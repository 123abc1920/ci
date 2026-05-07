#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "MainViewModel.h"
#include "Logger.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainViewModel &viewModel, Logger &logger, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMdiArea *mdiArea;

    MainViewModel viewModel;
    Logger &logger;

    string openFile();

    void updateMenuItems(QMdiSubWindow *activeWindow);

private slots:
    void onOpenFileTriggered();
    void onFilterBtnTriggered();
    void onSearchBtnTriggered();
    void onSaveBtnTriggered();
};

#endif