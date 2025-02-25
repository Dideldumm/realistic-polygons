//
// Created by dideldumm on 25.02.25.
//

#include <string>
#include <CGAL/draw_polygon_2.h>

#include "../PolygonGenerator/MergeConvexHulls.h"
#include "../utils/geometry/CgalTypes.h"
#include "../utils/PointGenerator/RingDistributionPointGenerator.h"

int main(int argc, char **argv) {
    const int number_of_points = std::stoi(argv[1]);
    RingDistributionPointGenerator point_generator(10, 15);
    std::list<CgalTypes::Point> points;
    std::ranges::copy(point_generator.generate_points(number_of_points), std::back_inserter(points));
    const CgalTypes::Polygon polygon = merge_convex_hulls_algorithm(points);
    CGAL::draw(polygon);
}
