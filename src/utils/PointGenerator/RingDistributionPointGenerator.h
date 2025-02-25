//
// Created by dideldumm on 27.10.24.
//

#ifndef RINGDISTRIBUTIONPOINTGENERATOR_H
#define RINGDISTRIBUTIONPOINTGENERATOR_H

#include <random>
#include "SeededPointGenerator.h"

typedef uint_least32_t u32;

class RingDistributionPointGenerator : public SeededPointGenerator {
private:
    const CgalTypes::Point origin;
    const double inner_radius;
    const double outer_radius;
    std::uniform_real_distribution<> angle_distribution;
    std::uniform_real_distribution<> distance_distribution;

    [[nodiscard]] CgalTypes::Point calculate_point(double angle, double distance) const;

public:
    explicit RingDistributionPointGenerator(double inner_radius, double outer_radius, CgalTypes::Point origin, const u32 &seed);

    explicit RingDistributionPointGenerator(double inner_radius, double outer_radius, const u32 &seed);

    explicit RingDistributionPointGenerator(double inner_radius, double outer_radius, const CgalTypes::Point &origin);

    explicit RingDistributionPointGenerator(double inner_radius, double outer_radius);

    std::vector<CgalTypes::Point> generate_points(unsigned int number_of_points) override;

    CgalTypes::Point generate_point() override;
};


#endif //RINGDISTRIBUTIONPOINTGENERATOR_H
