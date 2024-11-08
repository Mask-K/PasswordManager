#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QObject>

#include <vector>

#include <PasswordInfo.h>



class PasswordManager : public QObject
{
    Q_OBJECT
public:
    PasswordManager(QObject *parent = nullptr);

private:
    std::vector<PasswordInfo> passwords;
};

#endif // PASSWORDMANAGER_H
