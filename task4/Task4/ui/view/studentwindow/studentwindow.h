#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "StudentViewModel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class StudentWindow;
}
QT_END_NAMESPACE

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    StudentWindow(StudentViewModel &viewModel, QWidget *parent = nullptr);
    ~StudentWindow();

private:
    Ui::StudentWindow *ui;
    StudentViewModel &viewModel;
};

#endif