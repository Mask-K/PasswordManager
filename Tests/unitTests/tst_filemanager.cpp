
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

        FileManager::filename = "test_passwords.json";

        QFile::remove(FileManager::filename);
    }

    void TearDown() override {
        QFile::remove(FileManager::filename);
    }
};

TEST_F(FileManagerTest, GetSalt_ValidSalt) {
    QJsonObject root;
    root["salt"] = "test_salt";
    QJsonDocument doc(root);

    QFile file(FileManager::filename);
    ASSERT_TRUE(file.open(QIODevice::WriteOnly));
    file.write(doc.toJson());
    file.close();

    QString salt = FileManager::getSalt();
    ASSERT_EQ(salt, "test_salt");
}

TEST_F(FileManagerTest, AddPassword_Success) {
    FileManager::addPassword("example.com", "user1", "encrypted_password1");

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);

    QJsonObject entry = passwords.first();
    ASSERT_EQ(entry["site"].toString(), "example.com");
    ASSERT_EQ(entry["login"].toString(), "user1");
    ASSERT_EQ(entry["password"].toString(), "encrypted_password1");
}

TEST_F(FileManagerTest, DeletePassword_Success) {
    FileManager::addPassword("example1.com", "user1", "password1");
    FileManager::addPassword("example2.com", "user2", "password2");

    FileManager::deletePassword(1);

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);
    ASSERT_EQ(passwords.first()["site"].toString(), "example1.com");
}

TEST_F(FileManagerTest, DeletePassword_InvalidIndex) {
    FileManager::addPassword("example.com", "user1", "password1");

    FileManager::deletePassword(5);

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);
}

TEST_F(FileManagerTest, EditPassword_Success) {
    FileManager::addPassword("example.com", "user1", "password1");

    FileManager::editPassword("newsite.com", "newuser", "newpassword", 0);

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);

    QJsonObject entry = passwords.first();
    ASSERT_EQ(entry["site"].toString(), "newsite.com");
    ASSERT_EQ(entry["login"].toString(), "newuser");
    ASSERT_EQ(entry["password"].toString(), "newpassword");
}

TEST_F(FileManagerTest, EditPassword_InvalidIndex) {
    FileManager::addPassword("example.com", "user1", "password1");

    FileManager::editPassword("newsite.com", "newuser", "newpassword", 5);

    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_EQ(passwords.size(), 1);
    ASSERT_EQ(passwords.first()["site"].toString(), "example.com");
}

TEST_F(FileManagerTest, GetPasswords_EmptyFile) {
    QList<QJsonObject> passwords = FileManager::getPasswords();
    ASSERT_TRUE(passwords.isEmpty());
}

