#ifndef ATBASHCIPHER_H
#define ATBASHCIPHER_H

#include "IEncryptionAlgorithm.h"

/**
 * @brief The AtbashCipher class
 * Implements the Atbash cipher, a simple substitution cipher that maps A-Z to Z-A.
 * The key parameter is ignored since the mapping is fixed.
 */
class AtbashCipher : public IEncryptionAlgorithm {
public:
    AtbashCipher();

    /**
     * @brief Encrypts the given plain text using the Atbash cipher.
     * Since Atbash is symmetric, encryption and decryption are identical.
     * @param plainText The text to encrypt.
     * @param key Ignored.
     * @return The encrypted text.
     */
    QString encrypt(const QString &plainText, const QString &key) override;

    /**
     * @brief Decrypts the given cipher text using the Atbash cipher.
     * This operation is identical to encryption.
     * @param cipherText The text to decrypt.
     * @param key Ignored.
     * @return The decrypted (original) text.
     */
    QString decrypt(const QString &cipherText, const QString &key) override;
};

#endif // ATBASHCIPHER_H
