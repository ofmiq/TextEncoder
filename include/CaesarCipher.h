#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "IEncryptionAlgorithm.h"

/**
 * @brief The CaesarCipher class
 * Implements a simple Caesar cipher.
 */
class CaesarCipher : public IEncryptionAlgorithm {
public:
    /**
     * @brief Constructor for CaesarCipher with default shift value.
     * @param defaultShift The default shift value for the cipher (default is 3).
     */
    explicit CaesarCipher(int defaultShift = 3);

    /**
     * @brief Encrypts the given plain text using Caesar cipher.
     * @param plainText The text to encrypt.
     * @param key The shift key (integer as string).
     * @return The encrypted text.
     */
    QString encrypt(const QString &plainText, const QString &key) override;

    /**
     * @brief Decrypts the given cipher text using Caesar cipher.
     * @param cipherText The text to decrypt.
     * @param key The shift key (integer as string).
     * @return The decrypted text.
     */
    QString decrypt(const QString &cipherText, const QString &key) override;

private:
    int defaultShift;
};

#endif // CAESARCIPHER_H
