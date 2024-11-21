#include "passwordManager.h"

#include "encryptionKeyGenerator.h"
#include "fileManager.h"

PasswordManager::PasswordManager(QObject *parent) : QObject(parent)
{

}

void PasswordManager::addKey(const QString &password){
    qDebug() << "Add key";
    encryption.setKey(generatePBKDF2Key(password, FileManager::getSalt()));
}

void PasswordManager::addPassword(const QString& site, const QString& login, const QString& password){
    qDebug() << "Add";
    passwords.push_back({site, login, password});

    auto encryptedPassword = encryption.encrypt(password);

    FileManager::addPassword(site, login, encryptedPassword);

    emit passwordsUpdated();
}

void PasswordManager::deletePassword(int index){
    qDebug() << "Delete";
    passwords.erase(passwords.cbegin() + index);

    FileManager::deletePassword(index);

    emit passwordsUpdated();
}

void PasswordManager::editPassword(const QString& newSite, const QString& newLogin, const QString& newPassword, int index){
    qDebug() << "Edit";
    passwords[index] = {newSite, newLogin, newPassword};

    auto encryptedNewPassword = encryption.encrypt(newPassword);

    FileManager::editPassword(newSite, newLogin, encryptedNewPassword, index);

    emit passwordsUpdated();
}

QVector<PasswordInfo> PasswordManager::getPasswords(){

    qDebug() << FileManager::filename;
    qDebug() << "Get";

    passwords.clear();

    auto list = FileManager::getPasswords();

    for (const QJsonObject& passwordInfo : list){
        auto decryptedPassword = encryption.decrypt(passwordInfo["password"].toString());

        passwords.push_back({passwordInfo["site"].toString(), passwordInfo["login"].toString(), decryptedPassword});
    }
    return passwords;
}

QVariantList PasswordManager::getPasswords2() {

    getPasswords();

    QVariantList passwordsList;
    for (const auto &password : passwords) {
        QVariantMap passwordMap;
        passwordMap["site"] = password.site;
        passwordMap["login"] = password.login;
        passwordMap["password"] = password.password;
        passwordsList.append(passwordMap);
    }
    return passwordsList;
}
