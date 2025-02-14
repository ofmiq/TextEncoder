#ifndef CIPHERFACTORY_H
#define CIPHERFACTORY_H

#include <memory>
#include "IEncryptionAlgorithm.h"

/**
 * @brief The CipherFactory class
 * A factory class responsible for creating instances of encryption algorithms.
 */
class CipherFactory {
public:
    enum AlgorithmType {
        Caesar
    };

    /**
     * @brief Creates an encryption algorithm based on the specified type.
     * @param type The type of algorithm to create.
     * @return A unique_ptr to an IEncryptionAlgorithm object representing the created cipher.
     */
    static std::unique_ptr<IEncryptionAlgorithm> createCipher(AlgorithmType type);
};

#endif // CIPHERFACTORY_H
