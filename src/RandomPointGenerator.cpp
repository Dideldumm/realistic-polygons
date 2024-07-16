//
// Created by dideldumm on 12.07.24.
//

#include "RandomPointGenerator.h"
#include "CommandLineArgumentHandler.h"
#include "AlgoGeoUtils.h"

#define DEFAULT_ORIGIN {0,0}

u32 createSeed() {
    std::random_device os_seed;
    return os_seed();
}

NumberGenerator createNumberGenerator(const u32 seed) {
    const NumberGenerator generator(seed);
    return generator;
}

Point defaultOrigin() {
    return {0, 0};
}

std::uniform_real_distribution<> createDistribution(const double middle, const double radius) {
    const std::uniform_real_distribution<> distribution(middle - radius, middle + radius);
    return distribution;
}

RandomPointGenerator::RandomPointGenerator(const double radius,
                                           const Point origin,
                                           const u32 seed) : radius(radius),
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

RandomPointGenerator::RandomPointGenerator(const double radius, const Point origin) : RandomPointGenerator(
    radius, origin, createSeed()) {
}

RandomPointGenerator::RandomPointGenerator(const double radius, const u32 seed) : RandomPointGenerator(
    radius, defaultOrigin(), seed) {
}

RandomPointGenerator::RandomPointGenerator(const double radius) : RandomPointGenerator(
    radius, defaultOrigin(), createSeed()) {
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

RandomPointGenerator createPointGenerator(const std::optional<std::string> &maybeSeed,
                                          const std::optional<std::string> &maybeOrigin,
                                          const double radius) {
    Point origin;
    if (maybeOrigin.has_value()) {
        origin = parsePoint(maybeOrigin.value());
    } else {
        origin = {0, 0};
    }

    if (maybeSeed.has_value()) {
        return RandomPointGenerator(radius, origin, std::stoi(maybeSeed.value()));
    }
    return RandomPointGenerator(radius, origin);
}
