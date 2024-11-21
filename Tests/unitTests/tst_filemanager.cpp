
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "fileManager.h"

using namespace testing;

class FileManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Тимчасовий файл для тестів
        FileManager::filename = "test_passwords.json";

        // Очищення файлу перед кожним тестом
        QFile::remove(FileManager::filename);
    }

    void TearDown() override {
        // Видалення тестового файлу після завершення тестів
        QFile::remove(FileManager::filename);
    }
};

TEST_F(FileManagerTest, GetSalt_ValidSalt) {
    // Створення файлу з сіллю
    QJsonObject root;
    root["salt"] = "test_salt";
    QJsonDocument doc(root);

    QFile file(FileManager::filename);
    ASSERT_TRUE(file.open(QIODevice::WriteOnly));
    file.write(doc.toJson());
    file.close();

    // Перевірка отримання солі
    QString salt = FileManager::getSalt();
    ASSERT_EQ(salt, "test_salt");
}

TEST_F(FileManagerTest, AddPassword_Success) {
    // Додавання нового пароля
    FileManager::addPassword("example.com", "user1", "encrypted_password1");

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);

    QJsonObject entry = passwords.first();
    ASSERT_EQ(entry["site"].toString(), "example.com");
    ASSERT_EQ(entry["login"].toString(), "user1");
    ASSERT_EQ(entry["password"].toString(), "encrypted_password1");
}

TEST_F(FileManagerTest, DeletePassword_Success) {
    // Додавання декількох паролів
    FileManager::addPassword("example1.com", "user1", "password1");
    FileManager::addPassword("example2.com", "user2", "password2");

    // Видалення другого пароля
    FileManager::deletePassword(1);

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);
    ASSERT_EQ(passwords.first()["site"].toString(), "example1.com");
}

TEST_F(FileManagerTest, DeletePassword_InvalidIndex) {
    // Додавання одного пароля
    FileManager::addPassword("example.com", "user1", "password1");

    // Спроба видалення за невірним індексом
    FileManager::deletePassword(5);

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);  // Список паролів не повинен змінитися
}

TEST_F(FileManagerTest, EditPassword_Success) {
    // Додавання пароля
    FileManager::addPassword("example.com", "user1", "password1");

    // Редагування пароля
    FileManager::editPassword("newsite.com", "newuser", "newpassword", 0);

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);

    QJsonObject entry = passwords.first();
    ASSERT_EQ(entry["site"].toString(), "newsite.com");
    ASSERT_EQ(entry["login"].toString(), "newuser");
    ASSERT_EQ(entry["password"].toString(), "newpassword");
}

TEST_F(FileManagerTest, EditPassword_InvalidIndex) {
    // Додавання пароля
    FileManager::addPassword("example.com", "user1", "password1");

    // Спроба редагування за невірним індексом
    FileManager::editPassword("newsite.com", "newuser", "newpassword", 5);

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);  // Дані повинні залишитися незмінними
    ASSERT_EQ(passwords.first()["site"].toString(), "example.com");
}

TEST_F(FileManagerTest, GetPasswords_EmptyFile) {
    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_TRUE(passwords.isEmpty());  // Порожній список, якщо файлу немає або він пустий
}

