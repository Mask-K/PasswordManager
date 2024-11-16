#include "fileManager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

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

void FileManager::addPassword(const QString& site, const QString& login, const QString& encryptedPassword){
    QFile file(filename);

    QJsonObject rootObject;
    QJsonArray passwordsArray;

    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Could not open file for reading:" << file.errorString();
            return;
        }

        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument document = QJsonDocument::fromJson(fileData);
        if (!document.isNull() && document.isObject()) {
            rootObject = document.object();
            if (rootObject.contains("passwords") && rootObject["passwords"].isArray()) {
                passwordsArray = rootObject["passwords"].toArray();
            }
        }
    }

    QJsonObject newPasswordEntry;
    newPasswordEntry["site"] = site;
    newPasswordEntry["login"] = login;
    newPasswordEntry["password"] = encryptedPassword;

    passwordsArray.append(newPasswordEntry);

    rootObject["passwords"] = passwordsArray;
    QJsonDocument newDocument(rootObject);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }

    file.write(newDocument.toJson());
    file.close();

    qDebug() << "Password added successfully for site:" << site;
}

void FileManager::deletePassword(int index){
    QFile file(filename);

    if (!file.exists()) {
        qDebug() << "File does not exist.";
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading:" << file.errorString();
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(fileData);
    if (document.isNull() || !document.isObject()) {
        qDebug() << "Invalid JSON data.";
        return;
    }

    QJsonObject rootObject = document.object();

    if (!rootObject.contains("passwords") || !rootObject["passwords"].isArray()) {
        qDebug() << "No passwords array found in the file.";
        return;
    }

    QJsonArray passwordsArray = rootObject["passwords"].toArray();

    if (index < 0 || index >= passwordsArray.size()) {
        qDebug() << "Invalid index.";
        return;
    }

    passwordsArray.removeAt(index);

    rootObject["passwords"] = passwordsArray;

    QJsonDocument updatedDocument(rootObject);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }

    file.write(updatedDocument.toJson());
    file.close();

    qDebug() << "Password at index" << index << "deleted successfully.";
}

void FileManager::editPassword(const QString& newSite, const QString& newLogin, const QString& newEncryptedPassword, int index){
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading:" << file.errorString();
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(fileData);
    if (document.isNull() || !document.isObject()) {
        qDebug() << "Invalid JSON file structure.";
        return;
    }

    QJsonObject rootObject = document.object();
    if (!rootObject.contains("passwords") || !rootObject["passwords"].isArray()) {
        qDebug() << "No 'passwords' array found in the file.";
        return;
    }

    QJsonArray passwordsArray = rootObject["passwords"].toArray();

    if (index < 0 || index >= passwordsArray.size()) {
        qDebug() << "Index out of bounds.";
        return;
    }

    QJsonObject passwordEntry = passwordsArray[index].toObject();

    passwordEntry["site"] = newSite;
    passwordEntry["login"] = newLogin;
    passwordEntry["password"] = newEncryptedPassword;

    passwordsArray[index] = passwordEntry;

    rootObject["passwords"] = passwordsArray;
    QJsonDocument newDocument(rootObject);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }

    file.write(newDocument.toJson());
    file.close();

    qDebug() << "Password updated successfully at index:" << index;
}

QList<QJsonObject> FileManager::getPasswords(){
    QFile file(filename);

    // Перевіряємо, чи файл можна відкрити для читання
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading:" << file.errorString();
        return {};
    }

    QByteArray fileData = file.readAll();
    file.close();

    // Розбираємо JSON-файл
    QJsonDocument document = QJsonDocument::fromJson(fileData);
    if (document.isNull() || !document.isObject()) {
        qDebug() << "Invalid JSON file structure.";
        return {};
    }

    QJsonObject rootObject = document.object();
    if (!rootObject.contains("passwords") || !rootObject["passwords"].isArray()) {
        qDebug() << "No 'passwords' array found in the file.";
        return {};
    }

    QJsonArray passwordsArray = rootObject["passwords"].toArray();
    QList<QJsonObject> passwordsList;

    // Конвертуємо QJsonArray у QList<QJsonObject>
    for (const QJsonValue& value : passwordsArray) {
        if (value.isObject()) {
            passwordsList.append(value.toObject());
        }
    }

    return passwordsList;
};
