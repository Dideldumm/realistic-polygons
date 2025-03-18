//
// Created by dideldumm on 22.02.25.
//

#ifndef UNIONOFCONVEXHULLSGENERATOR_H
#define UNIONOFCONVEXHULLSGENERATOR_H
#include <list>

#include "../utils/geometry/CgalTypes.h"


CgalTypes::Polygon generate_random_convex_polygon(const std::list<CgalTypes::Point> &vertices);

CgalTypes::Polygon unionOfConvexHulls(unsigned int max_number_of_points, unsigned int number_of_polygons, double
                                      max_translation_distance);


#endif //UNIONOFCONVEXHULLSGENERATOR_H
