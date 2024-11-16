#ifndef AESENCRYPTION_H
#define AESENCRYPTION_H

#include "Encryption.h"

#include <QString>

class AESEncryption : public IEncryption
{
public:
    AESEncryption() = default;

    QString encrypt(const QString &data);
    QString decrypt(const QString &data);

    void setKey(const std::string& key);
private:
    QString key__;
};

#endif // AESENCRYPTION_H
