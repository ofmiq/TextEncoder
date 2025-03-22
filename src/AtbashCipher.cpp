#include "AtbashCipher.h"

AtbashCipher::AtbashCipher() {}

QString AtbashCipher::encrypt(const QString &plainText, const QString &key) {
    Q_UNUSED(key);
    QString result;
    for (const QChar &ch : plainText) {
        if (ch.isUpper()) {
            result.append(QChar(QChar('Z').unicode() - (ch.unicode() - QChar('A').unicode())));
        } else if (ch.isLower()) {
            result.append(QChar(QChar('z').unicode() - (ch.unicode() - QChar('a').unicode())));
        } else {
            result.append(ch);
        }
    }
    return result;
}

QString AtbashCipher::decrypt(const QString &cipherText, const QString &key) {
    return encrypt(cipherText, key);
}
