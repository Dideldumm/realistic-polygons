//
// Created by dideldumm on 14.12.24.
//

#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Vector_2.h>

#include "../PointGenerator/SeededPointGenerator.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Vector_2<Kernel> Vector;

/**
 * Transforms the given angle to a vector on the unit circle.
 * @param angle the angle to transformed
 * @return the calculated vector
 */
Vector map_angle_to_vector(const double &angle);

Vector create_random_vector(SeededPointGenerator &point_generator);

#endif //VECTORUTILS_H
