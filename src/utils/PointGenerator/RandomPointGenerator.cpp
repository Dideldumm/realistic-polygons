//
// Created by dideldumm on 12.07.24.
//

#include "RandomPointGenerator.h"
#include "../CommandLineArgumentHandler.h"

#define DEFAULT_ORIGIN {0,0}

Point defaultOrigin() {
    return {0, 0};
}

std::uniform_real_distribution<> createDistribution(const double middle, const double radius) {
    const std::uniform_real_distribution<> distribution(middle - radius, middle + radius);
    return distribution;
}

RandomPointGenerator::RandomPointGenerator(const double radius,
                                           const Point origin,
                                           const u32 seed) : RingDistributionPointGenerator(
    0, radius, origin, seed) {
}

RandomPointGenerator::RandomPointGenerator(const double radius, const Point origin) : RandomPointGenerator(
    radius, origin, create_seed()) {
}

RandomPointGenerator::RandomPointGenerator(const double radius, const u32 seed) : RandomPointGenerator(
    radius, defaultOrigin(), seed) {
}

RandomPointGenerator::RandomPointGenerator(const double radius) : RandomPointGenerator(
    radius, defaultOrigin(), create_seed()) {
}

RandomPointGenerator::RandomPointGenerator() : RandomPointGenerator(1) {
}
