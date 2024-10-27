//
// Created by dideldumm on 12.07.24.
//

#ifndef SEEDEDPOINTSETGENERATOR_H
#define SEEDEDPOINTSETGENERATOR_H

#include <random>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#include "RingDistributionPointGenerator.h"
#include "SeededPointGenerator.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef uint_least32_t u32;
typedef std::mt19937 NumberGenerator;

class RandomPointGenerator final : public RingDistributionPointGenerator {
public:
    explicit RandomPointGenerator(double radius, Point origin, u32 seed);

    explicit RandomPointGenerator(double radius, Point origin);

    explicit RandomPointGenerator(double radius, u32 seed);

    explicit RandomPointGenerator(double radius);

    explicit RandomPointGenerator();
};

#endif //SEEDEDPOINTSETGENERATOR_H
