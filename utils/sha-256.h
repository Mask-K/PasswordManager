#ifndef SHA256_H
#define SHA256_H

#include <openssl/evp.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <QString>

inline QString sha256(const QString& data) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to initialize SHA-256 context");
    }

    if (EVP_DigestUpdate(context, data.toStdString().c_str(), data.size()) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to update SHA-256 hash");
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    if (EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to finalize SHA-256 hash");
    }


    EVP_MD_CTX_free(context);

    std::stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return QString::fromStdString(ss.str());
}

#endif // SHA256_H
