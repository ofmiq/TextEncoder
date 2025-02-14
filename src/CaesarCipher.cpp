#include "CaesarCipher.h"

CaesarCipher::CaesarCipher(int defaultShift)
    : defaultShift(defaultShift)
{
}

QString CaesarCipher::encrypt(const QString &plainText, const QString &key) {
    bool ok;
    int shift = key.toInt(&ok);
    if (!ok)
        shift = defaultShift;
    QString result;
    for (QChar ch : plainText) {
        if (ch.isLetter()) {
            QChar base = ch.isUpper() ? 'A' : 'a';
            int offset = (ch.unicode() - base.unicode() + shift) % 26;
            result.append(QChar(base.unicode() + offset));
        } else {
            result.append(ch);
        }
    }
    return result;
}

QString CaesarCipher::decrypt(const QString &cipherText, const QString &key) {
    bool ok;
    int shift = key.toInt(&ok);
    if (!ok)
        shift = defaultShift;
    QString result;
    for (QChar ch : cipherText) {
        if (ch.isLetter()) {
            QChar base = ch.isUpper() ? 'A' : 'a';
            int offset = (ch.unicode() - base.unicode() - shift + 26) % 26;
            result.append(QChar(base.unicode() + offset));
        } else {
            result.append(ch);
        }
    }
    return result;
}
