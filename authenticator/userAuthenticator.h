#ifndef USERAUTHENTICATOR_H
#define USERAUTHENTICATOR_H

#include <QObject>

class UserAuthenticator : public QObject
{
    Q_OBJECT
public:
    UserAuthenticator(QObject *parent = nullptr);

    Q_INVOKABLE bool login(const QString& login, const QString& masterPassword);

    Q_INVOKABLE bool regist(const QString& login, const QString& masterPassword);

private:
    QString getFilename();
};

#endif // USERAUTHENTICATOR_H
