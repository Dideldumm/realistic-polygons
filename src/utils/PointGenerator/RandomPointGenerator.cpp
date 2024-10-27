//
// Created by dideldumm on 12.07.24.
//

#include "RandomPointGenerator.h"
#include "../CommandLineArgumentHandler.h"

#define DEFAULT_ORIGIN {0,0}

RandomPointGenerator::RandomPointGenerator(const double radius,
                                           const Point origin,
                                           const u32 seed) : RingDistributionPointGenerator(
    0, radius, origin, seed) {
}

RandomPointGenerator::RandomPointGenerator(const double radius, const Point origin) : RandomPointGenerator(
    radius, origin, create_seed()) {
}

RandomPointGenerator::RandomPointGenerator(const double radius, const u32 seed) : RandomPointGenerator(
    radius, DEFAULT_ORIGIN, seed) {
}

RandomPointGenerator::RandomPointGenerator(const double radius) : RandomPointGenerator(
    radius, DEFAULT_ORIGIN, create_seed()) {
}

RandomPointGenerator::RandomPointGenerator() : RandomPointGenerator(1) {
}
