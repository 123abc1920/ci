#include "filterwindow.h"
#include "ui_filterwindow.h"
#include <QStringListModel>
#include <QMdiSubWindow>

FilterWindow::FilterWindow(FilterViewModel *viewModel, QMdiArea *mdiArea, QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::FilterWindow>())
      ,
      m_viewModel(viewModel), m_mdiArea(mdiArea)
{
    ui->setupUi(this);

    if (m_viewModel)
    {
        m_viewModel->writeLog(Logger::Level::DEBUG, "Открыто окно фильтра");

        const auto &subjects = m_viewModel->getSubjects();
        for (const auto &subject : subjects)
        {
            ui->comboInclude->addItem(QString::fromStdString(subject));
            ui->comboExclude->addItem(QString::fromStdString(subject));
        }
    }

    connect(ui->addInclude, &QPushButton::clicked, [this]()
            {
        if (!m_viewModel) return;
        std::string selectedText = ui->comboInclude->currentText().toStdString();
        m_viewModel->addToQuery(selectedText, false);
        updateSubjectDataLists(); });

    connect(ui->addExclude, &QPushButton::clicked, [this]()
            {
        if (!m_viewModel) return;
        std::string selectedText = ui->comboExclude->currentText().toStdString();
        m_viewModel->addToQuery(selectedText, true);
        updateSubjectDataLists(); });
}

void FilterWindow::updateExcludes()
{
    if (!m_viewModel)
        return;
    auto *model = new QStringListModel(this);
    QStringList items;
    for (const auto &subject : m_viewModel->getQueryData(true))
    {
        items << QString::fromStdString(subject);
    }
    model->setStringList(items);

    auto *oldModel = ui->excludeList->model();
    ui->excludeList->setModel(model);
    if (oldModel)
        oldModel->deleteLater();
}

void FilterWindow::updateIncludes()
{
    if (!m_viewModel)
        return;
    auto *model = new QStringListModel(this);
    QStringList items;
    for (const auto &subject : m_viewModel->getQueryData(false))
    {
        items << QString::fromStdString(subject);
    }
    model->setStringList(items);

    auto *oldModel = ui->includeList->model();
    ui->includeList->setModel(model);
    if (oldModel)
        oldModel->deleteLater();
}

void FilterWindow::updateSubjectDataLists()
{
    if (!m_viewModel)
        return;
    updateExcludes();
    updateIncludes();
    ui->queryText->setText(QString::fromStdString(m_viewModel->getQueryText()));
}

FilterViewModel *FilterWindow::getViewModel() const
{
    return m_viewModel;
}

FilterWindow::~FilterWindow()
{
    if (m_viewModel)
    {
        m_viewModel->writeLog(Logger::Level::DEBUG, "Окно фильтров закрыто");
    }
}
