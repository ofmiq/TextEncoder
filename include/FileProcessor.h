#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QString>

/**
 * @brief The FileProcessor class
 * This class centralizes file reading and writing logic.
 */
class FileProcessor {
public:
    /**
     * @brief Loads all text content from a specified file.
     * @param filePath The absolute path to the file to read.
     * @return QString containing the file content.
     */
    static QString loadFromFile(const QString& filePath);

    /**
     * @brief Saves the given text content to a specified file.
     * @param filePath The absolute path to the file to write.
     * @param content The QString content to save to the file.
     * @return True if the file was successfully opened and written to, false otherwise.
     */
    static bool saveToFile(const QString& filePath, const QString& content);
};

#endif // FILEPROCESSOR_H