#include "fileManager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

QString FileManager::filename;

QString FileManager::getSalt()
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading:" << file.errorString();
        return {};
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(fileData);
    if (document.isNull() || !document.isObject()) {
        qDebug() << "Invalid JSON data";
        return {};
    }

    QJsonObject jsonObject = document.object();
    if (jsonObject.contains("salt") && jsonObject["salt"].isString()) {
        return jsonObject["salt"].toString();
    } else {
        qDebug() << "The key 'salt' does not exist";
        return {};
    }
}
