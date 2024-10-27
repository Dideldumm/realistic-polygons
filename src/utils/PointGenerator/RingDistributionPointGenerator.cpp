//
// Created by dideldumm on 27.10.24.
//

#include "RingDistributionPointGenerator.h"

std::uniform_real_distribution<> createDistribution(const double lower_boundary,
                                                    const double upper_boundary) {
    const std::uniform_real_distribution<> distribution(lower_boundary, upper_boundary);
    return distribution;
}

RingDistributionPointGenerator::RingDistributionPointGenerator(const double inner_radius, const double outer_radius,
                                                               Point origin,
                                                               const u32 seed) : SeededPointGenerator(
        seed, create_number_generator(seed)),
    inner_radius(inner_radius),
    outer_radius(outer_radius),
    angle_distribution(createDistribution(0, 360)),
    distance_distribution(createDistribution(inner_radius, outer_radius)) {
}

RingDistributionPointGenerator::RingDistributionPointGenerator(const double inner_radius, const double outer_radius,
                                                               const u32 seed) : RingDistributionPointGenerator(
    inner_radius, outer_radius, {0, 0}, seed) {
}

RingDistributionPointGenerator::RingDistributionPointGenerator(const double inner_radius, const double outer_radius,
                                                               const Point origin) : RingDistributionPointGenerator(
    inner_radius, outer_radius, origin, create_seed()) {
}

RingDistributionPointGenerator::RingDistributionPointGenerator(const double inner_radius,
                                                               const double
                                                               outer_radius) : RingDistributionPointGenerator(
    inner_radius, outer_radius, {0, 0}, create_seed()) {
}

Point calculate_point(const double angle, const double distance) {
    double x = distance * std::cos(angle);
    double y = distance * std::sin(angle);
    return {x, y};
}

std::vector<Point> RingDistributionPointGenerator::generate_points(const unsigned int number_of_points) {
    std::vector<Point> points{};
    for (unsigned int i = 0; i < number_of_points; ++i) {
        const double angle = this->angle_distribution(this->number_generator);
        const double distance = this->distance_distribution(this->number_generator);
        points.emplace_back(calculate_point(angle, distance));
    }
    return points;
}
