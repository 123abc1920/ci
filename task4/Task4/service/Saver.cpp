#include "Saver.h"
#include <QStringListModel>
#include <QIODevice>
#include <QFile>

Saver::Saver(Logger &logger) : ILoggable(logger) {}

string Saver::convertToString(vector<string> data)
{
    string result = "";

    for (auto &row : data)
    {
        result += row + "\n";
    }

    this->writeLog(Logger::Level::DEBUG, "Данные конвертированы в строку");

    return result;
}

bool Saver::save(vector<string> data, string filePath)
{
    QFile file(QString::fromStdString(filePath));

    this->writeLog(Logger::Level::INFO, "Выбран файл: " + filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        this->writeLog(Logger::Level::ERROR, "Не удается открыть файл");
        return false;
    }

    QTextStream out(&file);

    QString dataToSave = QString::fromStdString(this->convertToString(data));
    out << dataToSave;

    this->writeLog(Logger::Level::INFO, "Сохранено в файл " + filePath);

    file.close();
    return true;
}

Saver::~Saver() {}