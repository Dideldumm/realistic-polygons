//
// Created by dideldumm on 25.02.25.
//

#include <future>
#include <CGAL/draw_polygon_2.h>
#include <CGAL/random_polygon_2.h>

#include "../PolygonGenerator/GenerateSimplePolygon.h"
#include "../utils/geometry/CgalTypes.h"

int main() {
    constexpr double radius = 5;
    const CgalTypes::PointGenerator point_generator(15);
    std::vector<CgalTypes::Point> points;
    std::copy_n(point_generator, 120, std::back_inserter(points));
    CgalTypes::Polygon nonIntersectingPolygon = create_non_intersecting_polygon(points);

    std::future<void> noValue = std::async([nonIntersectingPolygon]() { CGAL::draw(nonIntersectingPolygon); });
    return 0;
}
