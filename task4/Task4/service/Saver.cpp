#include "Saver.h"
#include <QStringListModel>
#include <QIODevice>
#include <QFile>

Saver::Saver() {}

string Saver::convertToString(vector<string> data)
{
    string result = "";

    for (auto &row : data)
    {
        result += row + "\n";
    }

    return result;
}

bool Saver::save(vector<string> data, string filePath)
{
    QFile file(QString::fromStdString(filePath));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);

    QString dataToSave = QString::fromStdString(this->convertToString(data));
    out << dataToSave;

    file.close();
    return true;
}

Saver::~Saver() {}