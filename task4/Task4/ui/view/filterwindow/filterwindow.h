#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QMainWindow>
#include "FilterViewModel.h"
#include <QMdiArea>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class FilterWindow;
}
QT_END_NAMESPACE

class FilterWindow : public QMainWindow
{
    Q_OBJECT

public:
    FilterWindow(FilterViewModel &viewModel, QMdiArea *mdiArea, QWidget *parent = nullptr);
    ~FilterWindow();

private:
    Ui::FilterWindow *ui;
    FilterViewModel &viewModel;
    QMdiArea *mdiArea;

    void updateExcludes();
    void updateIncludes();
    void updateSubjectDataLists();
};

#endif