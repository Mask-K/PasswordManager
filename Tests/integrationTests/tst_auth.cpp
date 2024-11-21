#include <gtest/gtest.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "userAuthenticator.h"
#include "sha-256.h"

using namespace testing;

class UserAuthenticatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        testLogin = "testUser";
        testPassword = "testPassword123";
        testFile = sha256(testLogin + testPassword) + ".json";
    }

    void TearDown() override {
        QFile::remove(testFile);
    }

    QString testLogin;
    QString testPassword;
    QString testFile;
};

TEST_F(UserAuthenticatorTest, Login_ValidUser_ReturnsTrue) {
    QFile file(testFile);
    ASSERT_TRUE(file.open(QIODevice::WriteOnly));

    QJsonObject jsonObject;
    jsonObject["salt"] = "testSalt";
    QJsonDocument jsonDoc(jsonObject);

    file.write(jsonDoc.toJson());
    file.close();

    UserAuthenticator authenticator;
    bool result = authenticator.login(testLogin, testPassword);

    EXPECT_TRUE(result);
}

TEST_F(UserAuthenticatorTest, Login_InvalidUser_ReturnsFalse) {

    UserAuthenticator authenticator;
    bool result = authenticator.login(testLogin, testPassword);

    EXPECT_FALSE(result);
}


TEST_F(UserAuthenticatorTest, Register_NewUser_CreatesFile) {
    UserAuthenticator authenticator;

    bool result = authenticator.regist(testLogin, testPassword);
    EXPECT_TRUE(result);

    QFile file(testFile);
    EXPECT_TRUE(file.exists());

    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDoc.object();
        EXPECT_TRUE(jsonObject.contains("salt"));
    }

    file.remove();
}

