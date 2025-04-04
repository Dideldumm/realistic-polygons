//
// Created by dideldumm on 28.07.24.
//

#include <CGAL/draw_polygon_2.h>
#include <ranges>

#include "../utils/ToStringUtils.h"
#include "../TwoOptMoves.h"
#include "../utils/geometry/PolygonalChain.h"
#include "../utils/geometry/CgalTypes.h"


class PolygonalChain;

enum ShortestConnectionPosition {
    First,
    Last
};

std::tuple<ShortestConnectionPosition, ShortestConnectionPosition, double> minimalDistance(
    const PolygonalChain &a, const PolygonalChain &b);

void PolygonalChain::addAllElements(const bool forwards, const std::vector<CgalTypes::Point> &elements) {
    if (forwards) {
        for (auto point: elements) {
            this->elements.push_back(point);
        }
    } else {
        for (auto element: std::ranges::reverse_view(elements)) {
            this->elements.push_back(element);
        }
    }
}

std::vector<std::pair<PolygonalChain, PolygonalChain> > createAllPairs(const std::vector<PolygonalChain> &elements) {
    std::vector<std::pair<PolygonalChain, PolygonalChain> > pairs = {};
    for (unsigned int i = 0; i < elements.size(); ++i) {
        for (unsigned int j = i; j < elements.size(); ++j) {
            if (i != j) {
                pairs.emplace_back(elements[i], elements[j]);
            }
        }
    }
    return pairs;
}

CgalTypes::Point removeIntersections(const auto &polygonWithIntersections) {
    TwoOptMoves twoOptMoves;
    for (CgalTypes::Point point: polygonWithIntersections) {
        twoOptMoves.addPoint(point);
    }
    return twoOptMoves.getPolygon();
}

int main(const int argc, char **argv) {
    // initialize all points as polygonal objects
    const int numberOfPoints = argc > 1 ? std::stoi(argv[1]) : 12;

    CgalTypes::PointGenerator point_generator(30);
    std::vector<CgalTypes::Point> points;
    std::copy_n(point_generator, numberOfPoints, std::back_inserter(points));

    std::vector<PolygonalChain> objects;
    for (const auto &point: points) {
        objects.emplace_back(point);
    }

    while (objects.size() > 1) {
        auto pairs = createAllPairs(objects);
        double shortestDistance = std::numeric_limits<double>::max();
        PolygonalChain shortestA;
        PolygonalChain shortestB;
        for (const auto &[a, b]: pairs) {
            if (auto [connectorA, connectorB, distance] = minimalDistance(a, b); distance < shortestDistance) {
                shortestDistance = distance;
                shortestA = a;
                shortestB = b;
            }
        }
        std::erase(objects, shortestA);
        std::erase(objects, shortestB);
        PolygonalChain merged(shortestA, shortestB);
        objects.emplace_back(merged);
    }

    const std::vector<CgalTypes::Point> finalPolygonalChain = objects.front().getElements();
    const CgalTypes::Polygon polygonWithIntersections(finalPolygonalChain.begin(), finalPolygonalChain.end());
    CGAL::draw(polygonWithIntersections);
    if (!polygonWithIntersections.is_simple()) {
        std::cout << "polygon is not simple" << std::endl;
        const CgalTypes::Polygon polygon = removeIntersections(polygonWithIntersections.vertices());
        CGAL::draw(polygon);
    }
}
