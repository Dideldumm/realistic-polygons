//
// Created by dideldumm on 12.07.24.
//

#include "RandomPointGenerator.h"
#include "AlgoGeoUtils.h"

u32 createSeed() {
    std::random_device os_seed;
    return os_seed();
}

NumberGenerator createNumberGenerator(const u32 seed) {
    const NumberGenerator generator(seed);
    return generator;
}

std::uniform_real_distribution<> createDistribution(const double middle, const double radius) {
    const std::uniform_real_distribution<> distribution(middle - radius, middle + radius);
    return distribution;
}

RandomPointGenerator::RandomPointGenerator(const double radius,
                                           const Point origin = Point(0, 0),
                                           const u32 seed = createSeed()) : radius(radius),
                                                                            origin(origin),
                                                                            seed(seed),
                                                                            number_generator(
                                                                                createNumberGenerator(seed)),
                                                                            xDistribution(
                                                                                createDistribution(origin.x(), radius)),
                                                                            yDistribution(
                                                                                createDistribution(
                                                                                    origin.y(), radius)) {
}

RandomPointGenerator::RandomPointGenerator(double radius) : RandomPointGenerator(radius, {0, 0}, createSeed()) {
}


std::vector<Point> RandomPointGenerator::generatePoints(const unsigned int numberOfPoints) {
    std::vector<Point> points{};
    for (unsigned int i = 0; i < numberOfPoints; ++i) {
        double x = this->xDistribution(this->number_generator);
        double y = this->yDistribution(this->number_generator);
        points.emplace_back(x, y);
    }
    return points;
}
