//
// Created by Long Kenvy on 28/05/2022.
//

#ifndef CHAOTIC_CHAOTICCYPHER_H
#define CHAOTIC_CHAOTICCYPHER_H

#include <functional>
#include <memory>

#include "Utils.h"
#include "ChaoticMap.h"

class ChaoticCypher {
public:
    static constexpr int ENCRYPT_MODE = 0;
    static constexpr int DECRYPT_MODE = 1;

public:

    void init(int, const bytes &);

    void init(int, const std::string &);


    bytes doFinal(bytes &);

    bytes doFinal(std::string &);


    friend std::ostream &operator<<(std::ostream &, const ChaoticCypher &);

private:
    std::unique_ptr<ChaoticMap> permMap;
    std::unique_ptr<ChaoticMap> subMap;
    std::unique_ptr<ChaoticMap> diffMap;
    doubles keyPerm, keySub, keyDiff;
    int mode{};
    bytes data;
public:
    explicit ChaoticCypher(
            std::unique_ptr<ChaoticMap> permMap = std::make_unique<Logistic>(),
            std::unique_ptr<ChaoticMap> subMap = std::make_unique<Logistic>(),
            std::unique_ptr<ChaoticMap> diffMap = std::make_unique<Logistic>()
    );

    ChaoticCypher(ChaoticMap* permMap,ChaoticMap* subMap,ChaoticMap* diffMap);


public:
    void setMode(int);

    auto getData() const -> const bytes & {
        return data;
    }

    void setData(const bytes &data) {
        this->data = data;
    }

    bytes generateSBox();
    void permutation();
    void substitution();
    void diffusion();
    bytes encrypt();
    bytes decrypt();

private:
    const size_t IGNORE_ELEMENTS = 1000;
    const size_t ITER_GEN_SBOX_DEFAULT = 1000;
    const size_t SBOX_SIZE = 256;


    void setKey(bytes key);
};


#endif //CHAOTIC_CHAOTICCYPHER_H
