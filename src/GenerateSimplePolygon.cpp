#include <future>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/draw_polygon_2.h>
#include "utils/RandomPointGenerator.h"
#include "utils/geometry/AlgoGeoUtils.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;


Polygon create_non_intersecting_polygon(std::vector<Point> inputPoints) {
    //initialize points, leftmost and rightmost
    auto begin = inputPoints.begin();
    const auto end = inputPoints.end();
    std::unordered_set<Point> points{};
    Point leftmost = *begin;
    Point rightmost = leftmost;

    for (; begin != end; ++begin) {
        Point current_point = *begin;
        points.insert(current_point);
        if (is_left_of(current_point, leftmost)) {
            leftmost = current_point;
        }

        if (is_right_of(current_point, rightmost)) {
            rightmost = current_point;
        }
    }
    points.erase(rightmost);
    points.erase(leftmost);

    const Segment middle_line(leftmost, rightmost);

    std::set<Point, LeftComparator> a; //sorts points from left to right
    std::set<Point, RightComparator> b; //sorts points from right to left
    for (Point point: points) {
        if (is_above(point, middle_line)) {
            a.insert(point);
        } else {
            b.insert(point);
        }
    }

    Polygon polygon;
    polygon.push_back(leftmost);
    for (Point point: a) {
        polygon.push_back(point);
    }
    polygon.push_back(rightmost);
    for (Point point: b) {
        polygon.push_back(point);
    }
    return polygon;
}

int main() {
    constexpr double radius = 5;
    RandomPointGenerator random_point_generator(radius);
    const std::vector<Point> points = random_point_generator.generatePoints(120);
    Polygon nonIntersectingPolygon = create_non_intersecting_polygon(points);


    std::future<void> noValue = std::async([nonIntersectingPolygon]() { CGAL::draw(nonIntersectingPolygon); });

    // the draw function seems to work with simple polygons only
    // const Polygon polygon(input_begin, input_end);
    // std::future<void> nootherValue = std::async([polygon](){CGAL::draw(polygon);});
    return 0;
}
