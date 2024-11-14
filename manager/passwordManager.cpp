#include "passwordManager.h"

#include "encryptionKeyGenerator.h"
#include "fileManager.h"

PasswordManager::PasswordManager(QObject *parent) : QObject(parent)
{

}

void PasswordManager::addKey(const QString &password){
    encryption.setKey(generatePBKDF2Key(password, FileManager::getSalt()));
}
