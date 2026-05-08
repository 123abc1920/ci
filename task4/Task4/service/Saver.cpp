#include "Saver.h"
#include <QFile>
#include <QTextStream>

Saver::Saver(Logger &logger) : ILoggable(logger) {}

std::string Saver::convertToString(const std::vector<std::string> &data) const
{
    std::string result;

    for (const auto &row : data)
    {
        result += row;
        result += '\n';
    }

    writeLog(Logger::Level::DEBUG, "Данные конвертированы в строку");
    return result;
}

bool Saver::save(const std::vector<std::string> &data, std::string_view filePath) const
{
    QString qFilePath = QString::fromStdString(std::string(filePath));
    QFile file(qFilePath);

    writeLog(Logger::Level::INFO, "Попытка сохранения в файл: " + std::string(filePath));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        writeLog(Logger::Level::ERROR, "Не удается открыть файл для записи");
        return false;
    }

    QTextStream out(&file);
    out << QString::fromStdString(convertToString(data));

    writeLog(Logger::Level::INFO, "Успешно сохранено в файл");
    return true;
}
