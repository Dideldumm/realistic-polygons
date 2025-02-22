#include <future>
#include <CGAL/draw_polygon_2.h>
#include "../utils/PointGenerator/RandomPointGenerator.h"
#include "../utils/geometry/PointUtils.h"
#include "../utils/geometry/SegmentUtils.h"
#include "../utils/geometry/CgalTypes.h"


CgalTypes::Polygon create_non_intersecting_polygon(std::vector<Point> inputPoints) {
    //initialize points, leftmost and rightmost
    auto begin = inputPoints.begin();
    const auto end = inputPoints.end();
    std::vector<Point> points{};
    Point leftmost = *begin;
    Point rightmost = leftmost;

    for (; begin != end; ++begin) {
        Point current_point = *begin;
        points.emplace_back(current_point);
        if (is_left_of(current_point, leftmost)) {
            leftmost = current_point;
        }

        if (is_right_of(current_point, rightmost)) {
            rightmost = current_point;
        }
    }
    std::erase(points, rightmost);
    std::erase(points, leftmost);

    const CgalTypes::Segment middle_line(leftmost, rightmost);

    std::set<Point, bool(*)(const Point&, const Point&)> ascending_set(is_left_of); //sorts points from left to right
    std::set<Point, bool(*)(const Point&, const Point&)> descending_set(is_right_of); //sorts points from right to left
    for (const Point& point: points) {
        if (is_above(point, middle_line)) {
            ascending_set.insert(point);
        } else {
            descending_set.insert(point);
        }
    }

    CgalTypes::Polygon polygon;
    polygon.push_back(leftmost);
    for (const Point& point: ascending_set) {
        polygon.push_back(point);
    }
    polygon.push_back(rightmost);
    for (const Point& point: descending_set) {
        polygon.push_back(point);
    }
    return polygon;
}

int main() {
    constexpr double radius = 5;
    RandomPointGenerator random_point_generator(radius);
    const std::vector<Point> points = random_point_generator.generate_points(120);
    CgalTypes::Polygon nonIntersectingPolygon = create_non_intersecting_polygon(points);

    std::future<void> noValue = std::async([nonIntersectingPolygon]() { CGAL::draw(nonIntersectingPolygon); });
    return 0;
}
