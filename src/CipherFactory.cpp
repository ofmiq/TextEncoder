#include "CipherFactory.h"
#include "CaesarCipher.h"
#include "VigenereCipher.h"
#include "XORCipher.h"
#include "AtbashCipher.h"
#include "PlayfairCipher.h"

std::unique_ptr<IEncryptionAlgorithm> CipherFactory::createCipher(AlgorithmType type) {
    switch(type) {
    case Caesar:
        return std::make_unique<CaesarCipher>();
    case Vigenere:
        return std::make_unique<VigenereCipher>();
    case XOR:
        return std::make_unique<XORCipher>();
    case Atbash:
        return std::make_unique<AtbashCipher>();
    case Playfair:
        return std::make_unique<PlayfairCipher>();
    default:
        return nullptr;
    }
}
