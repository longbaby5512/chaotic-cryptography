//
// Created by nguye on 8/7/2022.
//

#ifndef CHAOTIC_LFSR_H
#define CHAOTIC_LFSR_H

#include "Utils.h"

class LFSR {
private:
    bytes data;
    int currentIndex{};
public:
    explicit LFSR(byte, int);

    byte operator[](int);
    double next();
};

#endif //CHAOTIC_LFSR_H
