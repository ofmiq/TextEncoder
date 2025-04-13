#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include "IEncryptionAlgorithm.h"
#include <QString>
#include <QVector>
#include <QPair>

/**
 * @brief The PlayfairCipher class
 * Implements the Playfair cipher for encryption and decryption.
 */
class PlayfairCipher : public IEncryptionAlgorithm {
public:
    PlayfairCipher();

    /**
     * @brief Encrypts the given plain text using the Playfair cipher.
     * @param plainText The text to encrypt.
     * @param key The key phrase used to build the Playfair table.
     * @return The encrypted text.
     */
    QString encrypt(const QString &plainText, const QString &key) override;

    /**
     * @brief Decrypts the given cipher text using the Playfair cipher.
     * @param cipherText The text to decrypt.
     * @param key The key phrase used to build the Playfair table.
     * @return The decrypted text.
     */
    QString decrypt(const QString &cipherText, const QString &key) override;

private:
    QVector<QVector<QChar>> table; // 5x5 Playfair table

    /**
     * @brief Prepares the 5x5 Playfair table using the given key.
     * @param key The key phrase.
     */
    void prepareTable(const QString &key);

    /**
     * @brief Processes the input text: removes spaces, converts to uppercase,
     * replaces 'J' with 'I', and inserts 'X' between duplicate letters if needed.
     * @param text The input text.
     * @param forEncryption Indicates if the processing is for encryption.
     * @return The processed text.
     */
    QString processText(const QString &text, bool forEncryption = true);

    /**
     * @brief Finds the position of a character in the Playfair table.
     * @param ch The character to find.
     * @return A pair (row, column) representing the character's position.
     */
    QPair<int, int> findPosition(QChar ch);

    /**
     * @brief Splits the processed text into digraphs, adding 'X' if needed.
     * @param text The processed text.
     * @return A vector of digraphs.
     */
    QVector<QPair<QChar, QChar>>createDigraphs(const QString &text, bool forEncryption = true);
};

#endif // PLAYFAIRCIPHER_H
