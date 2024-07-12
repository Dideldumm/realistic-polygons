//
// Created by dideldumm on 11.07.24.
//
#include <future>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Euclidean_distance.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/draw_polygon_2.h>
#include "AlgoGeoUtils.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Point_2<Kernel> Point;
typedef std::istream_iterator<Point> PointIterator;
typedef CGAL::Segment_2<Kernel> Segment;

Polygon generatePolygonForPermutation(const std::vector<Point> &points, const std::vector<int> &indices) {
    std::vector<Point> polygonPoints{};
    for (const int i: indices) {
        polygonPoints.push_back(points.at(i));
    }
    return {polygonPoints.begin(), polygonPoints.end()};
}

std::vector<Polygon> generateAllPolygonsForSetOfPoints(const std::vector<Point> &points) {
    std::vector<Polygon> polygons;
    std::vector<int> permutations;
    for (int i = 0; i < points.size(); ++i) {
        permutations.push_back(i);
    }
    do {
        Polygon currentPolygon = generatePolygonForPermutation(points, permutations);
        polygons.push_back(currentPolygon);
        if (currentPolygon.is_simple()) {
            std::future<void> noValue = std::async([currentPolygon]() { CGAL::draw(currentPolygon); });
        }
    } while (std::next_permutation(permutations.begin(), permutations.end()));
    return polygons;
}

double calculateDistance(const Point a, const Point b) {
    const double squaredDistance = CGAL::squared_distance(a, b);
    return sqrt(squaredDistance);
}

double calculateCircumference(const Polygon &polygon) {
    double circumference = 0;
    const Point firstPoint = *polygon.begin();

    auto previousPoint = polygon.begin();
    auto nextPoint = polygon.begin();
    const auto end = polygon.end();
    while (nextPoint != end) {
        const double distance = calculateDistance(*previousPoint, *nextPoint);
        circumference += distance;
        ++previousPoint;
        ++nextPoint;
    }
    const double lastDistance = calculateDistance(*previousPoint, firstPoint);
    circumference += lastDistance;
    return circumference;
}

std::vector<Point> getUserInput() {
    std::vector<Point> points;

    PointIterator input_begin(std::cin);
    for (const PointIterator input_end; input_begin != input_end; ++input_begin) {
        Point const current_point = *input_begin;
        points.push_back(current_point);
    }
    return points;
}

Polygon createShortestPolygon(const std::vector<Point> &points) {
    std::vector<Polygon> allPossiblePolygons = generateAllPolygonsForSetOfPoints(points);
    allPossiblePolygons.erase(std::remove_if(allPossiblePolygons.begin(), allPossiblePolygons.end(),
                                             [](const Polygon &polygon) { return !polygon.is_simple(); }),
                              allPossiblePolygons.end());

    Polygon shortest;
    double shortestCircumference = std::numeric_limits<double>::max();
    for (const auto &polygon: allPossiblePolygons) {
        if (const double circumference = calculateCircumference(polygon); circumference < shortestCircumference) {
            shortest = polygon;
            shortestCircumference = circumference;
        }
    }
    return shortest;
}

int main() {
    const std::vector<Point> userInput = getUserInput();
    Polygon shortestPolygon = createShortestPolygon(userInput);
    std::future<void> noValue = std::async([shortestPolygon]() { CGAL::draw(shortestPolygon); });
    return 0;
}
