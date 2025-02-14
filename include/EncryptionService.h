#ifndef ENCRYPTIONSERVICE_H
#define ENCRYPTIONSERVICE_H

#include <QString>
#include <memory>
#include "IEncryptionAlgorithm.h"

/**
 * @brief The EncryptionService class
 * Provides methods to encrypt and decrypt text using a given encryption algorithm.
 */
class EncryptionService {
public:
    /**
     * @brief Constructor for EncryptionService, initializing it with an encryption algorithm.
     * @param algorithm A unique_ptr to the encryption algorithm to be used.
     */
    explicit EncryptionService(std::unique_ptr<IEncryptionAlgorithm> algorithm);

    /**
     * @brief Sets the encryption algorithm to be used by the service.
     * @param algorithm A unique_ptr to the new encryption algorithm.
     */
    void setAlgorithm(std::unique_ptr<IEncryptionAlgorithm> algorithm);

    /**
     * @brief Encrypts the given plain text using the currently set algorithm.
     * @param plainText The text to encrypt.
     * @param key The encryption key.
     * @return The encrypted text.
     */
    QString encrypt(const QString &plainText, const QString &key);

    /**
     * @brief Decrypts the given cipher text using the currently set algorithm.
     * @param cipherText The text to decrypt.
     * @param key The decryption key.
     * @return The decrypted text.
     */
    QString decrypt(const QString &cipherText, const QString &key);

private:
    std::unique_ptr<IEncryptionAlgorithm> algorithm;
};

#endif // ENCRYPTIONSERVICE_H
