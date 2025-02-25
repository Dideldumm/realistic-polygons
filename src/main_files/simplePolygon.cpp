//
// Created by dideldumm on 25.02.25.
//

#include <future>
#include <CGAL/draw_polygon_2.h>

#include "../PolygonGenerator/GenerateSimplePolygon.h"
#include "../utils/geometry/CgalTypes.h"
#include "../utils/PointGenerator/RandomPointGenerator.h"

int main() {
    constexpr double radius = 5;
    RandomPointGenerator random_point_generator(radius);
    const std::vector<CgalTypes::Point> points = random_point_generator.generate_points(120);
    CgalTypes::Polygon nonIntersectingPolygon = create_non_intersecting_polygon(points);

    std::future<void> noValue = std::async([nonIntersectingPolygon]() { CGAL::draw(nonIntersectingPolygon); });
    return 0;
}
