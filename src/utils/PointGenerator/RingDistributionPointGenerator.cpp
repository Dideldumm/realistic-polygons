//
// Created by dideldumm on 27.10.24.
//

#include "RingDistributionPointGenerator.h"

#include <utility>

std::uniform_real_distribution<> createDistribution(const double lower_boundary,
                                                    const double upper_boundary) {
    const std::uniform_real_distribution<> distribution(lower_boundary, upper_boundary);
    return distribution;
}

RingDistributionPointGenerator::RingDistributionPointGenerator(const double inner_radius, const double outer_radius,
                                                               CgalTypes::Point origin,
                                                               const u32 &seed) : SeededPointGenerator(
        seed, create_number_generator(seed)),
    origin(std::move(origin)),
    inner_radius(inner_radius),
    outer_radius(outer_radius),
    angle_distribution(createDistribution(0, 360)),
    distance_distribution(createDistribution(inner_radius, outer_radius)) {
}

RingDistributionPointGenerator::RingDistributionPointGenerator(const double inner_radius, const double outer_radius,
                                                               const u32 &seed) : RingDistributionPointGenerator(
    inner_radius, outer_radius, {0, 0}, seed) {
}

RingDistributionPointGenerator::RingDistributionPointGenerator(const double inner_radius, const double outer_radius,
                                                               const CgalTypes::Point &origin) : RingDistributionPointGenerator(
    inner_radius, outer_radius, origin, create_seed()) {
}

RingDistributionPointGenerator::RingDistributionPointGenerator(const double inner_radius,
                                                               const double
                                                               outer_radius) : RingDistributionPointGenerator(
    inner_radius, outer_radius, {0, 0}, create_seed()) {
}

CgalTypes::Point RingDistributionPointGenerator::calculate_point(const double angle, const double distance) const {
    auto x = origin.x();
    x += distance * std::cos(angle);
    auto y = origin.y();
    y += distance * std::sin(angle);
    return {x, y};
}

std::vector<CgalTypes::Point> RingDistributionPointGenerator::generate_points(const unsigned int number_of_points) {
    std::vector<CgalTypes::Point> points{};
    for (unsigned int i = 0; i < number_of_points; ++i) {
        points.emplace_back(generate_point());
    }
    return points;
}

CgalTypes::Point RingDistributionPointGenerator::generate_point() {
    const double angle = this->angle_distribution(this->number_generator);
    const double distance = this->distance_distribution(this->number_generator);
    return calculate_point(angle, distance);
}
