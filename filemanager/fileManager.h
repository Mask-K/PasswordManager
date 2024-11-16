#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QJsonObject>

class FileManager
{
public:
    FileManager() = delete;

    static QString getSalt();
    static QList<QJsonObject> getPasswords();

    static void addPassword(const QString& site, const QString& login, const QString& encryptedPassword);

    static void deletePassword(int index);

    static void editPassword(const QString& newSite, const QString& newLogin, const QString& newEncryptedPassword, int index);

    static QString filename;
};

#endif // FILEMANAGER_H
