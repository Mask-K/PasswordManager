#ifndef AESENCRYPTION_H
#define AESENCRYPTION_H

#include <Encryption.h>

class AESEncryption : public IEncryption
{
public:
    AESEncryption() = default;

    QString encrypt(const QString &data, const QString &key){};
    QString decrypt(const QString &data, const QString &key){};
};

#endif // AESENCRYPTION_H
