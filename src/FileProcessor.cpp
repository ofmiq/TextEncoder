#include "FileProcessor.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>

QString FileProcessor::loadFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {};
    }

    QTextStream in(&file);
    return in.readAll();
}

bool FileProcessor::saveToFile(const QString& filePath, const QString& content) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out << content;
    return true;
}
