#ifndef IENCRYPTIONALGORITHM_H
#define IENCRYPTIONALGORITHM_H

#include <QString>

/**
 * @brief The IEncryptionAlgorithm interface
 * Defines the contract for encryption algorithms.
 */
class IEncryptionAlgorithm {
public:
    /**
     * @brief Virtual destructor for IEncryptionAlgorithm.
     */
    virtual ~IEncryptionAlgorithm() = default;

    /**
     * @brief Pure virtual function to encrypt the given plain text using the provided key.
     * @param plainText The text to encrypt.
     * @param key The key to use for encryption.
     * @return The encrypted text.
     */
    virtual QString encrypt(const QString &plainText, const QString &key) = 0;

    /**
     * @brief Pure virtual function to decrypt the given cipher text using the provided key.
     * @param cipherText The text to decrypt.
     * @param key The key to use for decryption.
     * @return The decrypted (original) text.
     */
    virtual QString decrypt(const QString &cipherText, const QString &key) = 0;
};

#endif // IENCRYPTIONALGORITHM_H
