#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <memory>
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
    explicit MainWindow(MainViewModel &viewModel, Logger &logger, QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<Ui::MainWindow> ui;

    MainViewModel &viewModel;
    Logger &logger;

    std::string openFile();
    void updateMenuItems(QMdiSubWindow *activeWindow);

private slots:
    void onOpenFileTriggered();
    void onFilterBtnTriggered();
    void onSearchBtnTriggered();
    void onSaveBtnTriggered();
};
#endif
