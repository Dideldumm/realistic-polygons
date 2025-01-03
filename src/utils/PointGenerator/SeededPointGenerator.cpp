//
// Created by dideldumm on 27.10.24.
//

#include <random>
#include "SeededPointGenerator.h"

u32 create_seed() {
    std::random_device os_seed;
    return os_seed();
}

NumberGenerator create_number_generator(const u32 &seed) {
    const NumberGenerator generator(seed);
    return generator;
}
