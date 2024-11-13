#ifndef SALTGENERATOR_H
#define SALTGENERATOR_H

#include <random>
#include <iomanip>

#include <QByteArray>

inline QByteArray generateSalt(size_t size = 16) {
    QByteArray salt;
    salt.resize(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    for (int i = 0; i < size; ++i) {
        salt[i] = static_cast<char>(dis(gen));
    }

    return salt;
}

#endif // SALTGENERATOR_H
