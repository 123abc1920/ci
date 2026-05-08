#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <memory> // Для unique_ptr
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
    explicit StudentWindow(StudentViewModel *viewModel, QWidget *parent = nullptr);
    ~StudentWindow() override;

    StudentViewModel *getViewModel() const;

private:
    std::unique_ptr<Ui::StudentWindow> ui;
    StudentViewModel *viewModel;
};

#endif
