#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QObject>
#include <QVector>
#include <QVariant>

#include "PasswordInfo.h"
#include "aesEncryption.h"


class PasswordManager : public QObject
{
    Q_OBJECT

signals:
    void passwordsUpdated();
    void passwordAdded(const QString& site, const QString& login, const QString& password);
    void passwordEdited(int index, const QString& site, const QString& login, const QString& password);
    void passwordDeleted(int index);

public:
    PasswordManager(QObject *parent = nullptr);

    Q_INVOKABLE void addKey(const QString &password);

    Q_INVOKABLE void addPassword(const QString& site, const QString& login, const QString& password);

    Q_INVOKABLE void deletePassword(int index);

    Q_INVOKABLE void editPassword(const QString& newSite, const QString& newLogin, const QString& newPassword, int index);

    Q_INVOKABLE QVariantList getPasswords();

private:
    QVector<PasswordInfo> getDataFromFile();

private:
    QVector<PasswordInfo> passwords;
    AESEncryption encryption;
};

#endif // PASSWORDMANAGER_H
