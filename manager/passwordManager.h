#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QObject>

#include <vector>

#include <PasswordInfo.h>
#include <aesEncryption.h>


class PasswordManager : public QObject
{
    Q_OBJECT
public:
    PasswordManager(QObject *parent = nullptr);

    Q_INVOKABLE void addKey(const QString &password);

private:
    std::vector<PasswordInfo> passwords;
    AESEncryption encryption;
};

#endif // PASSWORDMANAGER_H
