//
// Created by dideldumm on 21.02.25.
//

#ifndef CGALPOLYGONGENERATOR_H
#define CGALPOLYGONGENERATOR_H

#include "../utils/geometry/CgalTypes.h"

CgalTypes::Polygon generate_simple_polygon(const int &number_of_vertices);

std::vector<CgalTypes::Polygon> generate_polygons(const int &number_of_polygons, const int &max_number_of_vertices);


#endif //CGALPOLYGONGENERATOR_H
