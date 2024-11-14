#ifndef ENCRYPTIONKEYGENERATOR_H
#define ENCRYPTIONKEYGENERATOR_H

#include <openssl/evp.h>
#include <openssl/sha.h>

#include <QString>
#include <QByteArray>
#include <QDebug>

#include "constants.h"

inline std::string generatePBKDF2Key(const QString &password, const QString &salt, int iterations = 10000) {
    std::string key(constants::keyLength, '\0');

    if (PKCS5_PBKDF2_HMAC(password.toUtf8().constData(), password.size(),
                          reinterpret_cast<const unsigned char*>(salt.data()), salt.size(),
                          iterations, EVP_sha256(), constants::keyLength,
                          reinterpret_cast<unsigned char*>(&key[0])) == 0) {
        qDebug() << "Key generation failed.";
        return {};
    }

    return key;
}

#endif // ENCRYPTIONKEYGENERATOR_H
