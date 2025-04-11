//
// Created by dideldumm on 17.12.24.
//

#include <CGAL/Polygon_2.h>

#include "../PolygonGenerator/UnionOfConvexHullsGenerator.h"
#include "../utils/ToStringUtils.h"

int main(int argc, char **argv) {
    const unsigned int number_of_polygons = std::stoi(argv[1]);
    const unsigned int max_number_of_points = std::stoi(argv[2]);
    const double max_translation_distance = std::stod(argv[3]);
    const CgalTypes::Polygon result = union_of_convex_hulls(max_number_of_points, number_of_polygons, max_translation_distance);



}
