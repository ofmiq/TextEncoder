#include "EncryptionService.h"

EncryptionService::EncryptionService(std::unique_ptr<IEncryptionAlgorithm> algorithm)
    : algorithm(std::move(algorithm))
{
}

void EncryptionService::setAlgorithm(std::unique_ptr<IEncryptionAlgorithm> algorithm) {
    this->algorithm = std::move(algorithm);
}

QString EncryptionService::encrypt(const QString &plainText, const QString &key) {
    if (algorithm)
        return algorithm->encrypt(plainText, key);
    return QString();
}

QString EncryptionService::decrypt(const QString &cipherText, const QString &key) {
    if (algorithm)
        return algorithm->decrypt(cipherText, key);
    return QString();
}
