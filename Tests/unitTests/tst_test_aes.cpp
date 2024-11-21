
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <aesEncryption.h>

using namespace testing;

TEST(AESEncryptionTest, EncryptionDecryption) {
    AESEncryption aes;
    aes.setKey("test_key");

    QString plaintext = "Hello, World!";
    QString encrypted = aes.encrypt(plaintext);

    ASSERT_FALSE(encrypted.isEmpty()) << "Encrypted text should not be empty.";

    QString decrypted = aes.decrypt(encrypted);

    ASSERT_EQ(plaintext, decrypted) << "Decrypted text should match the original plaintext.";
}

TEST(AESEncryptionTest, DifferentKeys) {
    AESEncryption aes1;
    AESEncryption aes2;

    aes1.setKey("key_one");
    aes2.setKey("key_two");

    QString plaintext = "Hello, Encryption!";
    QString encrypted = aes1.encrypt(plaintext);

    ASSERT_FALSE(encrypted.isEmpty()) << "Encrypted text should not be empty.";

    QString decrypted = aes2.decrypt(encrypted);

    ASSERT_NE(plaintext, decrypted) << "Decryption with a different key should not return the original plaintext.";
}

TEST(AESEncryptionTest, EmptyInput) {
    AESEncryption aes;
    aes.setKey("test_key");

    QString plaintext = "";
    QString encrypted = aes.encrypt(plaintext);

    ASSERT_FALSE(encrypted.isEmpty()) << "Even empty plaintext should produce non-empty encrypted text.";

    QString decrypted = aes.decrypt(encrypted);

    ASSERT_EQ(plaintext, decrypted) << "Decrypted empty text should match the original empty plaintext.";
}

TEST(AESEncryptionTest, InvalidCiphertext) {
    AESEncryption aes;
    aes.setKey("test_key");

    QString invalidCiphertext = "invalid_base64_text";

    QString decrypted = aes.decrypt(invalidCiphertext);

    ASSERT_TRUE(decrypted.isEmpty()) << "Decryption of invalid ciphertext should return an empty result.";
}


