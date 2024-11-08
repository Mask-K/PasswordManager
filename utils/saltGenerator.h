#ifndef SALTGENERATOR_H
#define SALTGENERATOR_H

#include <vector>
#include <random>
#include <iomanip>

std::vector<uint8_t> generateSalt(size_t size = 16) {
    std::vector<uint8_t> salt(size);
    std::random_device rd;  // Використовується для ініціалізації генератора випадкових чисел
    std::mt19937 gen(rd()); // Створюємо генератор випадкових чисел Mersenne Twister
    std::uniform_int_distribution<> dis(0, 255); // Діапазон від 0 до 255 для байтів

    for (size_t i = 0; i < size; ++i) {
        salt[i] = static_cast<uint8_t>(dis(gen)); // Заповнюємо кожен байт випадковим значенням
    }

    return salt;
}

#endif // SALTGENERATOR_H
