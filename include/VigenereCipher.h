#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include "IEncryptionAlgorithm.h"

/**
 * @brief The VigenereCipher class
 * Implements the Vigenère cipher for encrypting and decrypting text.
 */
class VigenereCipher : public IEncryptionAlgorithm {
public:
    VigenereCipher();

    /**
     * @brief Encrypts the given plain text using the Vigenère cipher.
     * @param plainText The text to encrypt.
     * @param key The key phrase to use for encryption.
     * @return The encrypted text.
     */
    QString encrypt(const QString &plainText, const QString &key) override;

    /**
     * @brief Decrypts the given cipher text using the Vigenère cipher.
     * @param cipherText The text to decrypt.
     * @param key The key phrase to use for decryption.
     * @return The decrypted (original) text.
     */
    QString decrypt(const QString &cipherText, const QString &key) override;
};

#endif // VIGENERECIPHER_H
