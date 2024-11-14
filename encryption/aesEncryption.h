#ifndef AESENCRYPTION_H
#define AESENCRYPTION_H

#include <Encryption.h>

#include <string>

class AESEncryption : public IEncryption
{
public:
    AESEncryption() = default;

    QString encrypt(const QString &data, const QString &key){};
    QString decrypt(const QString &data, const QString &key){};

    void setKey(const std::string& key);
private:
    std::string key__;
};

#endif // AESENCRYPTION_H
