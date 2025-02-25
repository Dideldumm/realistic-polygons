//
// Created by dideldumm on 12.07.24.
//

#ifndef SEEDEDPOINTSETGENERATOR_H
#define SEEDEDPOINTSETGENERATOR_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#include "RingDistributionPointGenerator.h"
#include "SeededPointGenerator.h"


typedef uint_least32_t u32;

class RandomPointGenerator final : public RingDistributionPointGenerator {
public:
    explicit RandomPointGenerator(double radius, const CgalTypes::Point &origin, u32 seed);

    explicit RandomPointGenerator(double radius, const CgalTypes::Point &origin);

    explicit RandomPointGenerator(double radius, u32 seed);

    explicit RandomPointGenerator(double radius);

    explicit RandomPointGenerator();
};

#endif //SEEDEDPOINTSETGENERATOR_H
