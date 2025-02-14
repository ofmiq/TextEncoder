#include "CipherFactory.h"
#include "CaesarCipher.h"

std::unique_ptr<IEncryptionAlgorithm> CipherFactory::createCipher(AlgorithmType type) {
    switch(type) {
    case Caesar:
        return std::make_unique<CaesarCipher>();
    default:
        return nullptr;
    }
}
