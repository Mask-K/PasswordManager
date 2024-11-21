#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "passwordManager.h"

class PasswordManagerTest : public ::testing::Test {
protected:
    PasswordManager* manager;


    void SetUp() override {
        manager = new PasswordManager();

    }

    void TearDown() override {
        delete manager;
    }
};


TEST_F(PasswordManagerTest, AddPassword) {
    QString site = "example.com";
    QString login = "user";
    QString password = "securepassword123";


    manager->addPassword(site, login, password);

    auto passwordsList = manager->getPasswords();
    bool found = false;
    for (const auto& item : passwordsList) {
        if (item.toMap()["site"].toString() == site && item.toMap()["login"].toString() == login) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

TEST_F(PasswordManagerTest, DeletePassword) {
    QString site = "example.com";
    QString login = "user";
    QString password = "securepassword123";

    manager->addPassword(site, login, password);

    auto passwordsListBefore = manager->getPasswords();
    int initialSize = passwordsListBefore.size();

    manager->deletePassword(0);

    auto passwordsListAfter = manager->getPasswords();
    EXPECT_EQ(passwordsListAfter.size(), initialSize - 1);
}

TEST_F(PasswordManagerTest, EditPassword) {
    QString site = "example.com";
    QString login = "user";
    QString password = "securepassword123";

    manager->addPassword(site, login, password);

    QString newSite = "newexample.com";
    QString newLogin = "newuser";
    QString newPassword = "newsecurepassword";


    manager->editPassword(newSite, newLogin, newPassword, 0);

    auto passwordsList = manager->getPasswords();
    EXPECT_EQ(passwordsList[0].toMap()["site"].toString(), newSite);
    EXPECT_EQ(passwordsList[0].toMap()["login"].toString(), newLogin);
    EXPECT_EQ(passwordsList[0].toMap()["password"].toString(), newPassword);
}

TEST_F(PasswordManagerTest, IsDuplicate) {
    QString site = "example.com";
    QString login = "user";
    QString password = "securepassword123";

    manager->addPassword(site, login, password);


    bool result = manager->isDuplicate(site, login);
    EXPECT_TRUE(result);
}

TEST_F(PasswordManagerTest, GetPassword) {
    QString site = "example.com";
    QString login = "user";
    QString password = "securepassword123";

    manager->addPassword(site, login, password);

    QString storedPassword = manager->getPassword(0);
    EXPECT_EQ(storedPassword, password);
}
