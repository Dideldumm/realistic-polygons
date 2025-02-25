//
// Created by dideldumm on 25.02.25.
//

#ifndef GENERATESIMPLEPOLYGON_H
#define GENERATESIMPLEPOLYGON_H

#include "../utils/geometry/CgalTypes.h"

CgalTypes::Polygon create_non_intersecting_polygon(std::vector<CgalTypes::Point> inputPoints);

#endif //GENERATESIMPLEPOLYGON_H
