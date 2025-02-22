#include "XORCipher.h"
#include <QByteArray>

XORCipher::XORCipher() {}

QString XORCipher::encrypt(const QString &plainText, const QString &key) {
    if (key.isEmpty())
        return plainText;

    QByteArray plainBytes = plainText.toUtf8();
    QByteArray keyBytes = key.toUtf8();
    QByteArray result;
    int keyLen = keyBytes.size();

    for (int i = 0; i < plainBytes.size(); ++i) {
        char c = plainBytes.at(i);
        char k = keyBytes.at(i % keyLen);
        result.append(c ^ k);
    }

    return QString(result.toHex());
}

QString XORCipher::decrypt(const QString &cipherText, const QString &key) {
    if (key.isEmpty())
        return cipherText;

    QByteArray cipherBytes = QByteArray::fromHex(cipherText.toUtf8());
    QByteArray keyBytes = key.toUtf8();
    QByteArray result;
    int keyLen = keyBytes.size();

    for (int i = 0; i < cipherBytes.size(); ++i) {
        char c = cipherBytes.at(i);
        char k = keyBytes.at(i % keyLen);
        result.append(c ^ k);
    }
    return QString::fromUtf8(result);
}
