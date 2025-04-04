//
// Created by dideldumm on 25.02.25.
//

#include <string>
#include <CGAL/draw_polygon_2.h>
#include <CGAL/random_polygon_2.h>

#include "../PolygonGenerator/MergeConvexHulls.h"
#include "../utils/geometry/CgalTypes.h"

int main(int argc, char **argv) {
    const int number_of_points = std::stoi(argv[1]);

    const CgalTypes::PointGenerator point_generator(15);
    std::list<CgalTypes::Point> points;
    CGAL::copy_n_unique(point_generator, number_of_points, std::back_inserter(points));
    const CgalTypes::Polygon polygon = merge_convex_hulls_algorithm(points);
    CGAL::draw(polygon);
}
