#include "userAuthenticator.h"

#include <QFileInfo>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <fileManager.h>
#include <sha-256.h>
#include <saltGenerator.h>


UserAuthenticator::UserAuthenticator(QObject *parent) : QObject(parent)
{
}

bool UserAuthenticator::login(const QString &login, const QString &masterPassword)
{
    auto filename = sha256((login+masterPassword)) + ".json";

    if(QFileInfo::exists(filename) && QFileInfo(filename).isFile()){
        FileManager::filename = filename;
        return true;
    }
    return false;
}

bool UserAuthenticator::regist(const QString &login, const QString &masterPassword)
{
    auto filename = sha256((login+masterPassword)) + ".json";

    qDebug() << "Filename:" << filename;

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Не вдалося створити файл:" << file.errorString();
        return false;
    }

    QJsonObject jsonObject;
    jsonObject["salt"] = QString::fromLatin1(generateSalt());;
    QJsonDocument jsonDoc(jsonObject);

    file.write(jsonDoc.toJson());
    file.close();

    FileManager::filename = filename;

    return true;
}


