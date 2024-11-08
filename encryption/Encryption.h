#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>

class IEncryption{
public:
    virtual QString encrypt(const QString& data, const QString& key) = 0;
    virtual QString decrypt(const QString& data, const QString& key) = 0;

    virtual ~IEncryption() = default;
};

#endif // ENCRYPTION_H
