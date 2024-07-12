//
// Created by dideldumm on 12.07.24.
//

#ifndef SEEDEDPOINTSETGENERATOR_H
#define SEEDEDPOINTSETGENERATOR_H

#include <random>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef uint_least32_t u32;
typedef std::mt19937 NumberGenerator;

class RandomPointGenerator {
private:
    const double radius;
    const Point origin;
    const u32 seed;
    NumberGenerator number_generator;
    std::uniform_real_distribution<> xDistribution;
    std::uniform_real_distribution<> yDistribution;

public:
    explicit RandomPointGenerator(double radius, Point origin, u32 seed);

    [[nodiscard]] std::vector<Point> generatePoints(unsigned int numberOfPoints);
};

#endif //SEEDEDPOINTSETGENERATOR_H
