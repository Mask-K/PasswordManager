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

    emit passwordAdded(site, login, password);
}

void PasswordManager::deletePassword(int index){
    qDebug() << "Delete";
    passwords.erase(passwords.cbegin() + index);

    FileManager::deletePassword(index);

    emit passwordDeleted(index);
}

void PasswordManager::editPassword(const QString& newSite, const QString& newLogin, const QString& newPassword, int index){
    qDebug() << "Edit";
    passwords[index] = {newSite, newLogin, newPassword};

    auto encryptedNewPassword = encryption.encrypt(newPassword);

    FileManager::editPassword(newSite, newLogin, encryptedNewPassword, index);

    emit passwordEdited(index, newSite, newLogin, newPassword);
}

QVector<PasswordInfo> PasswordManager::getDataFromFile(){

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

QVariantList PasswordManager::getPasswords() {

    getDataFromFile();

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

bool PasswordManager::isDuplicate(const QString &site, const QString &login, int index) const{
    for (int i = 0; i < passwords.size(); ++i) {
        if (passwords[i].site == site && passwords[i].login == login && i != index) {
            return true;
        }
    }
    return false;
}

QString PasswordManager::getPassword(int index) {
    return passwords[index].password;
}
