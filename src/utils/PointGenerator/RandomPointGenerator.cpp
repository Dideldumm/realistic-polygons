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
                                           const u32 seed) : SeededPointGenerator(seed, create_number_generator(seed)),
                                                             radius(radius),
                                                             origin(origin),
                                                             xDistribution(
                                                                 createDistribution(origin.x(), radius)),
                                                             yDistribution(
                                                                 createDistribution(
                                                                     origin.y(), radius)) {
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

std::vector<Point> RandomPointGenerator::generate_points(const unsigned int number_of_points) {
    std::vector<Point> points{};
    for (unsigned int i = 0; i < number_of_points; ++i) {
        double x = this->xDistribution(this->number_generator);
        double y = this->yDistribution(this->number_generator);
        points.emplace_back(x, y);
    }
    return points;
}
