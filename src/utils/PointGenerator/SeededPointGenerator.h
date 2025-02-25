//
// Created by dideldumm on 27.10.24.
//

#ifndef POINTGENERATOR_H
#define POINTGENERATOR_H

#include <random>

#include "../geometry/CgalTypes.h"

typedef uint_least32_t u32;
typedef std::mt19937 NumberGenerator;

class SeededPointGenerator {
private:
    const u32 seed;

protected:
    NumberGenerator number_generator;

    SeededPointGenerator(const u32 &seed, const NumberGenerator &number_generator) : seed(seed),
        number_generator(number_generator) {
    }

public:
    virtual ~SeededPointGenerator() = default;

    [[nodiscard]] virtual std::vector<CgalTypes::Point> generate_points(unsigned int numberOfPoints) = 0;

    [[nodiscard]] virtual CgalTypes::Point generate_point() = 0;
};

u32 create_seed();

NumberGenerator create_number_generator(const u32 &seed);

#endif //POINTGENERATOR_H
