
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <encryptionKeyGenerator.h>
#include <saltGenerator.h>
#include <sha-256.h>

using namespace testing;

TEST(EncryptionKeyGeneratorTest, GenerateKeySuccess) {
    QString password = "test_password";
    QString salt = "test_salt";
    std::string key = generatePBKDF2Key(password, salt);

    ASSERT_FALSE(key.empty()) << "Generated key should not be empty.";
    ASSERT_EQ(key.size(), constants::keyLength) << "Generated key should have the correct length.";
}

TEST(SaltGeneratorTest, GenerateSaltDefaultSize) {
    QByteArray salt = generateSalt();

    ASSERT_EQ(salt.size(), 16) << "Default salt size should be 16 bytes.";
    ASSERT_NE(salt, QByteArray(16, 0)) << "Generated salt should not be all zeroes.";
}

TEST(SaltGeneratorTest, GenerateSaltCustomSize) {
    size_t customSize = 32;
    QByteArray salt = generateSalt(customSize);

    ASSERT_EQ(salt.size(), static_cast<int>(customSize)) << "Generated salt should have the custom size.";
}

TEST(SHA256Test, HashSuccess) {
    QString data = "test_data";
    QString hash = sha256(data);

    ASSERT_FALSE(hash.isEmpty()) << "SHA-256 hash should not be empty.";
    ASSERT_EQ(hash.size(), 64) << "SHA-256 hash should be 64 characters long.";
}

TEST(SHA256Test, HashEmptyString) {
    QString emptyData = "";
    QString hash = sha256(emptyData);

    ASSERT_FALSE(hash.isEmpty()) << "SHA-256 hash of an empty string should not be empty.";
    ASSERT_EQ(hash.size(), 64) << "SHA-256 hash of an empty string should be 64 characters long.";
}


