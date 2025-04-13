#include "PlayfairCipher.h"
#include <QSet>
#include <QChar>
#include <QDebug>

PlayfairCipher::PlayfairCipher() {
    // Table will be prepared in prepareTable()
}

void PlayfairCipher::prepareTable(const QString &key) {
    // Initialize a 5x5 table with spaces
    table = QVector<QVector<QChar>>(5, QVector<QChar>(5, ' '));

    QString processedKey;
    // Remove spaces, convert to uppercase, and replace J with I
    for (QChar ch : key.toUpper()) {
        if (ch.isLetter()) {
            if (ch == 'J') {
                ch = 'I';
            }
            processedKey.append(ch);
        }
    }

    // Remove duplicate letters
    QSet<QChar> seen;
    QString uniqueKey;
    for (QChar ch : processedKey) {
        if (!seen.contains(ch)) {
            seen.insert(ch);
            uniqueKey.append(ch);
        }
    }

    // Build alphabet without J
    QString alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    // Build table string
    QString tableString = uniqueKey;
    for (QChar ch : alphabet) {
        if (!tableString.contains(ch)) {
            tableString.append(ch);
        }
    }

    // Fill the 5x5 table
    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            table[i][j] = tableString.at(index++);
        }
    }
}

QPair<int, int> PlayfairCipher::findPosition(QChar ch) {
    if (ch == 'J')
        ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == ch) {
                return qMakePair(i, j);
            }
        }
    }
    return qMakePair(-1, -1);
}

QString PlayfairCipher::processText(const QString &text, bool forEncryption) {
    QString result;
    // Remove non-letter characters, convert to uppercase, and replace J with I
    for (QChar ch : text.toUpper()) {
        if (ch.isLetter()) {
            result.append(ch == 'J' ? 'I' : ch);
        }
    }
    if (forEncryption) {
        QString processed;
        int i = 0;
        while (i < result.length()) {
            processed.append(result[i]);
            if (i + 1 < result.length() && result[i] == result[i+1]) {
                processed.append('X');
                i++;
            } else {
                if (i + 1 < result.length())
                    processed.append(result[i+1]);
                i += 2;
            }
        }
        if (processed.length() % 2 != 0)
            processed.append('X');
        return processed;
    }
    return result;
}

QVector<QPair<QChar, QChar>> PlayfairCipher::createDigraphs(const QString &text, bool forEncryption) {
    QVector<QPair<QChar, QChar>> digraphs;
    for (int i = 0; i < text.length(); i += 2) {
        if (i + 1 < text.length()) {
            QChar first = text.at(i);
            QChar second = text.at(i + 1);
            digraphs.append(qMakePair(first, second));
        } else if (forEncryption && i < text.length()) {
            digraphs.append(qMakePair(text.at(i), QChar('X')));
        }
        // No padding for decryption if odd length.
    }
    return digraphs;
}

QString PlayfairCipher::encrypt(const QString &plainText, const QString &key) {
    prepareTable(key);
    QString processed = processText(plainText, true);
    QVector<QPair<QChar, QChar>> digraphs = createDigraphs(processed, true);
    QString result;

    for (auto pair : digraphs) {
        QPair<int, int> pos1 = findPosition(pair.first);
        QPair<int, int> pos2 = findPosition(pair.second);

        if (pos1.first == pos2.first) { // Same row: shift right
            int col1 = (pos1.second + 1) % 5;
            int col2 = (pos2.second + 1) % 5;
            result.append(table[pos1.first][col1]);
            result.append(table[pos2.first][col2]);
        } else if (pos1.second == pos2.second) { // Same column: shift down
            int row1 = (pos1.first + 1) % 5;
            int row2 = (pos2.first + 1) % 5;
            result.append(table[row1][pos1.second]);
            result.append(table[row2][pos2.second]);
        } else { // Rectangle swap
            result.append(table[pos1.first][pos2.second]);
            result.append(table[pos2.first][pos1.second]);
        }
    }
    return result;
}

QString PlayfairCipher::decrypt(const QString &cipherText, const QString &key) {
    prepareTable(key);
    QString processed = processText(cipherText, false);
    QVector<QPair<QChar, QChar>> digraphs = createDigraphs(processed, false);
    QString result;

    for (auto pair : digraphs) {
        QPair<int, int> pos1 = findPosition(pair.first);
        QPair<int, int> pos2 = findPosition(pair.second);

        if (pos1.first == pos2.first) { // Same row: shift left
            int col1 = (pos1.second + 4) % 5;
            int col2 = (pos2.second + 4) % 5;
            result.append(table[pos1.first][col1]);
            result.append(table[pos2.first][col2]);
        } else if (pos1.second == pos2.second) { // Same column: shift up
            int row1 = (pos1.first + 4) % 5;
            int row2 = (pos2.first + 4) % 5;
            result.append(table[row1][pos1.second]);
            result.append(table[row2][pos2.second]);
        } else { // Rectangle swap
            result.append(table[pos1.first][pos2.second]);
            result.append(table[pos2.first][pos1.second]);
        }
    }
    return result;
}
