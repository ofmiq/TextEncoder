#ifndef XORCIPHER_H
#define XORCIPHER_H

#include "IEncryptionAlgorithm.h"

/**
 * @brief The XORCipher class
 * Implements a simple XOR cipher for encryption and decryption.
 * The encrypted output is returned as a hexadecimal string.
 */
class XORCipher : public IEncryptionAlgorithm {
public:
    XORCipher();

    /**
     * @brief Encrypts the given plain text using XOR with the provided key.
     * The result is returned as a hexadecimal string.
     * @param plainText The text to encrypt.
     * @param key The key to use for XOR encryption.
     * @return The encrypted text in hex format.
     */
    QString encrypt(const QString &plainText, const QString &key) override;

    /**
     * @brief Decrypts the given hexadecimal encoded cipher text using XOR with the provided key.
     * @param cipherText The hex encoded text to decrypt.
     * @param key The key to use for XOR decryption.
     * @return The decrypted (original) text.
     */
    QString decrypt(const QString &cipherText, const QString &key) override;
};

#endif // XORCIPHER_H
