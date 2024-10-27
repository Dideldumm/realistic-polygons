//
// Created by dideldumm on 27.10.24.
//

#ifndef RINGDISTRIBUTIONPOINTGENERATOR_H
#define RINGDISTRIBUTIONPOINTGENERATOR_H
#include "../geometry/SeededPointGenerator.h"

typedef uint_least32_t u32;

class RingDistributionPointGenerator final : SeededPointGenerator {

    explicit RingDistributionPointGenerator(double inner_radius, double outer_radius, Point origin, u32 seed);

    explicit RingDistributionPointGenerator(double inner_radius, double outer_radius, u32 seed);

    explicit RingDistributionPointGenerator(double inner_radius, double outer_radius, Point origin);

    explicit RingDistributionPointGenerator(double inner_radius, double outer_radius);

    std::vector<Point> generate_points(unsigned int numberOfPoints) override;

};



#endif //RINGDISTRIBUTIONPOINTGENERATOR_H
