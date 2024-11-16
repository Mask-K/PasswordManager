#include "passwordManager.h"

#include "encryptionKeyGenerator.h"
#include "fileManager.h"

PasswordManager::PasswordManager(QObject *parent) : QObject(parent)
{

}

void PasswordManager::addKey(const QString &password){
    encryption.setKey(generatePBKDF2Key(password, FileManager::getSalt()));
}

void PasswordManager::addPassword(const QString& site, const QString& login, const QString& password){
    passwords.push_back({site, login, password});

    auto encryptedPassword = encryption.encrypt(password);

    FileManager::addPassword(site, login, encryptedPassword);
}

void PasswordManager::deletePassword(int index){
    passwords.erase(passwords.cbegin() + index);

    FileManager::deletePassword(index);
}

void PasswordManager::editPassword(const QString& newSite, const QString& newLogin, const QString& newPassword, int index){
    passwords[index] = {newSite, newLogin, newPassword};

    auto encryptedNewPassword = encryption.encrypt(newPassword);

    FileManager::editPassword(newSite, newLogin, encryptedNewPassword, index);
}

QVector<PasswordInfo> PasswordManager::getPasswords(){

    return passwords;
}
