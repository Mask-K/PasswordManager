#include "aesEncryption.h"

#include <openssl/evp.h>
#include <openssl/rand.h>

#include <QString>
#include <QByteArray>
#include <QDebug>

#include "constants.h"

void AESEncryption::setKey(const std::string& key){
    key__ = key;
}

QString AESEncryption::encrypt(const QString &data, const QString &key){

    QByteArray keyBytes = key.toUtf8().leftJustified(constants::keyLength, '\0');
    QByteArray iv(constants::ivLength, 0);

    if (RAND_bytes(reinterpret_cast<unsigned char*>(iv.data()), constants::ivLength) != 1) {
        qDebug() << "Failed to generate IV.";
        return {};
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    QByteArray ciphertext(data.toUtf8().size() + EVP_CIPHER_block_size(EVP_aes_256_gcm()), 0);

    int len = 0;
    int ciphertextLen = 0;

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) {
        qDebug() << "Encryption initialization failed.";
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    EVP_EncryptInit_ex(ctx, nullptr, nullptr,
                       reinterpret_cast<const unsigned char*>(keyBytes.constData()),
                       reinterpret_cast<const unsigned char*>(iv.constData()));

    if (EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(ciphertext.data()), &len,
                          reinterpret_cast<const unsigned char*>(data.toUtf8().constData()), data.toUtf8().size()) != 1) {
        qDebug() << "Encryption failed.";
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }
    ciphertextLen = len;

    QByteArray tag(constants::tagLength, 0);
    if (EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(ciphertext.data()) + len, &len) != 1) {
        qDebug() << "Final encryption step failed.";
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }
    ciphertextLen += len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, constants::tagLength, reinterpret_cast<unsigned char*>(tag.data())) != 1) {
        qDebug() << "Failed to get GCM tag.";
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    EVP_CIPHER_CTX_free(ctx);

    QByteArray result = iv + ciphertext.left(ciphertextLen) + tag;

    return result.toBase64();
}

QString AESEncryption::decrypt(const QString &data, const QString &key){
    QByteArray keyBytes = key.toUtf8().leftJustified(constants::keyLength, '\0');
    QByteArray encryptedData = QByteArray::fromBase64(data.toUtf8());

    QByteArray iv = encryptedData.left(constants::ivLength);
    QByteArray ciphertext = encryptedData.mid(constants::ivLength, encryptedData.size() - constants::ivLength - constants::tagLength);
    QByteArray tag = encryptedData.right(constants::tagLength);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    QByteArray decryptedText(ciphertext.size(), 0);

    int len = 0;
    int plaintextLen = 0;

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) {
        qDebug() << "Decryption initialization failed.";
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    EVP_DecryptInit_ex(ctx, nullptr, nullptr,
                       reinterpret_cast<const unsigned char*>(keyBytes.constData()),
                       reinterpret_cast<const unsigned char*>(iv.constData()));

    if (EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(decryptedText.data()), &len,
                          reinterpret_cast<const unsigned char*>(ciphertext.constData()), ciphertext.size()) != 1) {
        qDebug() << "Decryption failed.";
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }
    plaintextLen = len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, constants::tagLength, reinterpret_cast<unsigned char*>(tag.data())) != 1) {
        qDebug() << "Failed to set GCM tag.";
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    if (EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(decryptedText.data()) + len, &len) != 1) {
        qDebug() << "Decryption verification failed.";
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }
    plaintextLen += len;

    EVP_CIPHER_CTX_free(ctx);

    decryptedText.resize(plaintextLen);

    return QString::fromUtf8(decryptedText);
}
