#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <memory>
#include "FilterViewModel.h"

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
    explicit FilterWindow(FilterViewModel *viewModel, QMdiArea *mdiArea, QWidget *parent = nullptr);
    ~FilterWindow() override;

    FilterViewModel *getViewModel() const;

private:
    std::unique_ptr<Ui::FilterWindow> ui;

    FilterViewModel *viewModel;
    QMdiArea *mdiArea;

    void updateExcludes();
    void updateIncludes();
    void updateSubjectDataLists();
};

#endif
