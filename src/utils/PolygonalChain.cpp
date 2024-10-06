//
// Created by dideldumm on 06.10.24.
//

#include "PolygonalChain.h"

enum ShortestConnectionPosition {
    First,
    Last
};

std::tuple<ShortestConnectionPosition, ShortestConnectionPosition, double> minimalDistance(
    const PolygonalChain &a, const PolygonalChain &b);

void PolygonalChain::addAllElements(const bool forwards, const std::vector<Point> &elements) {
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

PolygonalChain::PolygonalChain(const PolygonalChain &a, const PolygonalChain &b) {
    auto [connectorA, connectorB, distance] = minimalDistance(a, b);
    addAllElements(connectorA == Last, a.elements);
    addAllElements(connectorB == First, b.elements);
}

std::tuple<ShortestConnectionPosition, ShortestConnectionPosition, double> minimalDistance(
    const PolygonalChain &a, const PolygonalChain &b) {
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