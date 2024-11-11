#include "userAuthenticator.h"

#include <QFileInfo>

#include <fileManager.h>
#include <sha-256.h>


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
    FileManager::filename = sha256((login+masterPassword));

}


