//
// Created by dideldumm on 11.07.24.
//

#include <argparse/argparse.hpp>
#include <CGAL/Euclidean_distance.h>
#include <CGAL/draw_polygon_2.h>

#include "BruteForceShortestPolygon.h"
#include "../utils/ToStringUtils.h"

typedef std::istream_iterator<CgalTypes::Point> PointIterator;

CgalTypes::Polygon generatePolygonForPermutation(const std::vector<CgalTypes::Point> &points, const std::vector<unsigned int> &indices) {
    std::vector<CgalTypes::Point> polygonPoints{};
    for (const unsigned int i: indices) {
        polygonPoints.push_back(points.at(i));
    }
    return {polygonPoints.begin(), polygonPoints.end()};
}

std::vector<CgalTypes::Polygon> generateAllPolygonsForSetOfPoints(const std::vector<CgalTypes::Point> &points) {
    std::vector<CgalTypes::Polygon> polygons;
    std::vector<unsigned int> permutations;
    for (unsigned int i = 0; i < points.size(); ++i) {
        permutations.push_back(i);
    }
    do {
        CgalTypes::Polygon currentPolygon = generatePolygonForPermutation(points, permutations);
        polygons.push_back(currentPolygon);
    } while (std::ranges::next_permutation(permutations).found);
    return polygons;
}

auto calc_sum_of_squared_edges(const CgalTypes::Polygon &polygon) {
    CgalTypes::Kernel::FT circumference(0);
    for (auto edge: polygon.edges()) {
        const CgalTypes::Kernel::FT length = edge.squared_length();
        circumference += length;
    }
    std::cout << "Polygon: " << polygonToString(polygon) << "with circumference: " << circumference << std::endl;
    return circumference;
}

std::vector<CgalTypes::Point> getUserInput() {
    std::vector<CgalTypes::Point> points;

    PointIterator input_begin(std::cin);
    for (const PointIterator input_end; input_begin != input_end; ++input_begin) {
        CgalTypes::Point const& current_point = *input_begin;
        points.push_back(current_point);
    }
    return points;
}

CgalTypes::Polygon createShortestPolygon(const std::vector<CgalTypes::Point> &points) {
    std::vector<CgalTypes::Polygon> allPossiblePolygons = generateAllPolygonsForSetOfPoints(points);
    erase_if(allPossiblePolygons, [](const CgalTypes::Polygon &polygon) { return !polygon.is_simple(); });

    CgalTypes::Polygon shortest;
    CgalTypes::Kernel::FT shortestCircumference(std::numeric_limits<double>::max());
    for (const auto &polygon: allPossiblePolygons) {
        if (const auto circumference = calc_sum_of_squared_edges(polygon); circumference < shortestCircumference) {
            shortest = polygon;
            shortestCircumference = circumference;
        }
    }
    return shortest;
}
