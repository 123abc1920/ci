#pragma once

#include <QMainWindow>
#include <QMdiArea>
#include "ResultViewModel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ResultWindow;
}
QT_END_NAMESPACE

class ResultWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultWindow(ResultViewModel &viewModel, QWidget *parent = nullptr);
    ~ResultWindow();

private:
    Ui::ResultWindow *ui;
    ResultViewModel &viewModel;
};