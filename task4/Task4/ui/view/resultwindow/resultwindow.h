#pragma once

#include <QMainWindow>
#include <memory>
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
    explicit ResultWindow(ResultViewModel *viewModel, QWidget *parent = nullptr);
    ~ResultWindow() override;

    ResultViewModel *getViewModel() const;

private:
    std::unique_ptr<Ui::ResultWindow> ui;
    ResultViewModel *viewModel;
};
