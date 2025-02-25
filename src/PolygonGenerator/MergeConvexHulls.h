//
// Created by dideldumm on 25.02.25.
//

#ifndef MERGECONVEXHULLS_H
#define MERGECONVEXHULLS_H

#include "../utils/geometry/CgalTypes.h"

CgalTypes::Polygon merge_convex_hulls_algorithm(const std::list<CgalTypes::Point> &vertices);



#endif //MERGECONVEXHULLS_H
