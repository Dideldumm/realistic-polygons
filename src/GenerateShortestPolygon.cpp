//
// Created by dideldumm on 11.07.24.
//
#include <future>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Euclidean_distance.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/draw_polygon_2.h>
#include "utils/AlgoGeoUtils.h"
#include "utils/CommandLineArgumentHandler.h"
#include "utils/RandomPointGenerator.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Point_2<Kernel> Point;
typedef std::istream_iterator<Point> PointIterator;
typedef CGAL::Segment_2<Kernel> Segment;

Polygon generatePolygonForPermutation(const std::vector<Point> &points, const std::vector<unsigned int> &indices) {
    std::vector<Point> polygonPoints{};
    for (const unsigned int i: indices) {
        polygonPoints.push_back(points.at(i));
    }
    return {polygonPoints.begin(), polygonPoints.end()};
}

std::vector<Polygon> generateAllPolygonsForSetOfPoints(const std::vector<Point> &points) {
    std::vector<Polygon> polygons;
    std::vector<unsigned int> permutations;
    for (unsigned int i = 0; i < points.size(); ++i) {
        permutations.push_back(i);
    }
    do {
        Polygon currentPolygon = generatePolygonForPermutation(points, permutations);
        polygons.push_back(currentPolygon);
    } while (std::next_permutation(permutations.begin(), permutations.end()));
    return polygons;
}

double calculateDistance(const Point a, const Point b) {
    const double squaredDistance = CGAL::squared_distance(a, b);
    return sqrt(squaredDistance);
}

double calculateCircumference(const Polygon &polygon) {
    double circumference = 0;
    for (auto edge: polygon.edges()) {
        const double length = sqrt(edge.squared_length());
        circumference += length;
    }
    std::cout << "Polygon: " << polygonToString(polygon) << "with circumference: " << circumference << std::endl;
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


int main(const int argc, char *argv[]) {
    const int numberOfPoints = std::stoi(getMandatoryCMDLineOption(argv, argv + argc, "-n"));
    const double radius = std::stod(getMandatoryCMDLineOption(argv, argv + argc, "-r"));
    const std::optional<std::string> maybeSeed = getCMDLineOption(argv, argv + argc, "-s");
    const std::optional<std::string> maybeOrigin = getCMDLineOption(argv, argv + argc, "-o");

    RandomPointGenerator generator = createPointGenerator(maybeSeed, maybeOrigin,
                                                          radius);
    std::vector<Point> points = generator.generatePoints(numberOfPoints);

    for (const Point point: points) {
        std::cout << pointToString(point) << std::endl;
    }
    std::cout << "And now we wait" << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    const Polygon polygon = createShortestPolygon(points);
    const auto stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Finished and took " << duration.count() << " seconds." << std::endl;
    std::future<void> noValue = std::async([polygon]() { CGAL::draw(polygon); });
}
