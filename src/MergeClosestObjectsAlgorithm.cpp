//
// Created by dideldumm on 28.07.24.
//

#include <CGAL/draw_polygon_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include "utils/AlgoGeoUtils.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Polygon_2<Kernel> Polygon;

class PolygonalObject;

enum ShortestConnectionPosition {
    First,
    Last
};

std::tuple<ShortestConnectionPosition, ShortestConnectionPosition, double> minimalDistance(
    const PolygonalObject &a, const PolygonalObject &b);

class PolygonalObject {
private:
    std::vector<Point> elements;

    void addAllElements(const bool forwards, const std::vector<Point> &elements) {
        if (forwards) {
            for (auto point: elements) {
                this->elements.push_back(point);
            }
        } else {
            for (auto begin = elements.rbegin(); begin != elements.rend(); ++begin) {
                this->elements.push_back(*begin);
            }
        }
    }

public:
    explicit PolygonalObject() = default;

    explicit PolygonalObject(Point p) {
        elements = {p};
    }

    explicit PolygonalObject(const PolygonalObject &a, const PolygonalObject &b);

    [[nodiscard]] Point getLastElement() const {
        return elements.back();
    }

    [[nodiscard]] Point getFirstElement() const {
        return elements.front();
    }

    [[nodiscard]] std::string toString() const {
        return polygonToString(Polygon(elements.begin(), elements.end()));
    }

    [[nodiscard]] std::vector<Point> getElements() const {
        return elements;
    };

    bool operator==(const PolygonalObject &other) const {
        return other.elements == this->elements;
    }
};

std::vector<std::pair<PolygonalObject, PolygonalObject> > createAllPairs(const std::vector<PolygonalObject> &elements) {
    std::vector<std::pair<PolygonalObject, PolygonalObject> > pairs = {};
    for (unsigned int i = 0; i < elements.size(); ++i) {
        for (unsigned int j = i; j < elements.size(); ++j) {
            if (i != j) {
                pairs.emplace_back(elements[i], elements[j]);
            }
        }
    }
    return pairs;
}

std::tuple<ShortestConnectionPosition, ShortestConnectionPosition, double> minimalDistance(
    const PolygonalObject &a, const PolygonalObject &b) {
    double shortestDistance = CGAL::squared_distance(a.getFirstElement(), b.getFirstElement());
    ShortestConnectionPosition connectorA = First;
    ShortestConnectionPosition connectorB = First;
    if (const double firstLastDistance = CGAL::squared_distance(a.getFirstElement(), b.getLastElement());
        shortestDistance > firstLastDistance) {
        shortestDistance = firstLastDistance;
        connectorA = First;
        connectorB = Last;
    }
    if (const double lastFirstDistance = CGAL::squared_distance(a.getLastElement(), b.getFirstElement());
        shortestDistance > lastFirstDistance) {
        shortestDistance = lastFirstDistance;
        connectorA = Last;
        connectorB = First;
    }
    if (const double lastLastDistance = CGAL::squared_distance(a.getLastElement(), b.getLastElement());
        shortestDistance > lastLastDistance) {
        shortestDistance = lastLastDistance;
        connectorA = Last;
        connectorB = Last;
    }
    return {connectorA, connectorB, shortestDistance};
}

PolygonalObject::PolygonalObject(const PolygonalObject &a, const PolygonalObject &b) {
    auto [connectorA, connectorB, distance] = minimalDistance(a, b);
    addAllElements(connectorA == Last, a.elements);
    addAllElements(connectorB == First, b.elements);
}

int main() {
    // initialize all points as polygonal objects
    std::vector<Point> input = {{0, 0}, {1, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}};
    std::vector<PolygonalObject> objects;
    for (const auto point: input) {
        objects.emplace_back(point);
    }

    while (objects.size() > 1) {
        auto pairs = createAllPairs(objects);
        double shortestDistance = std::numeric_limits<double>::max();
        PolygonalObject shortestA;
        PolygonalObject shortestB;
        for (const auto &[a, b]: pairs) {
            if (auto [connectorA, connectorB, distance] = minimalDistance(a, b); distance < shortestDistance) {
                shortestDistance = distance;
                shortestA = a;
                shortestB = b;
            }
        }
        objects.erase(std::remove(objects.begin(), objects.end(), shortestA), objects.end());
        objects.erase(std::remove(objects.begin(), objects.end(), shortestB), objects.end());
        PolygonalObject merged(shortestA, shortestB);
        objects.emplace_back(merged);
    }

    const auto finalPolygonalChain = objects.front().getElements();
    const Polygon polygon(finalPolygonalChain.begin(), finalPolygonalChain.end());
    const std::string points = polygonToString(polygon);
    std::cout << "final Polygon: " << points << std::endl;
    CGAL::draw(polygon);
}
