#include "VigenereCipher.h"
#include <QChar>

VigenereCipher::VigenereCipher() {}

QString VigenereCipher::encrypt(const QString &plainText, const QString &key) {
    QString result;
    int keyLen = key.length();
    if (keyLen == 0) {
        return plainText;
    }
    int keyIndex = 0;
    for (int i = 0; i < plainText.size(); ++i) {
        QChar ch = plainText.at(i);
        if (ch.isLetter()) {
            int shift = 0;
            QChar keyChar = key.at(keyIndex % keyLen);
            if (keyChar.isLetter()) {
                if (keyChar.isUpper()) {
                    shift = keyChar.unicode() - 'A';
                } else {
                    shift = keyChar.unicode() - 'a';
                }
            }
            if (ch.isUpper()) {
                int base = 'A';
                int offset = (ch.unicode() - base + shift) % 26;
                result.append(QChar(base + offset));
            } else {
                int base = 'a';
                int offset = (ch.unicode() - base + shift) % 26;
                result.append(QChar(base + offset));
            }
            keyIndex++;
        } else {
            result.append(ch);
        }
    }
    return result;
}

QString VigenereCipher::decrypt(const QString &cipherText, const QString &key) {
    QString result;
    int keyLen = key.length();
    if (keyLen == 0) {
        return cipherText;
    }
    int keyIndex = 0;
    for (int i = 0; i < cipherText.size(); ++i) {
        QChar ch = cipherText.at(i);
        if (ch.isLetter()) {
            int shift = 0;
            QChar keyChar = key.at(keyIndex % keyLen);
            if (keyChar.isLetter()) {
                if (keyChar.isUpper()) {
                    shift = keyChar.unicode() - 'A';
                } else {
                    shift = keyChar.unicode() - 'a';
                }
            }
            if (ch.isUpper()) {
                int base = 'A';
                int offset = (ch.unicode() - base - shift + 26) % 26;
                result.append(QChar(base + offset));
            } else {
                int base = 'a';
                int offset = (ch.unicode() - base - shift + 26) % 26;
                result.append(QChar(base + offset));
            }
            keyIndex++;
        } else {
            result.append(ch);
        }
    }
    return result;
}
