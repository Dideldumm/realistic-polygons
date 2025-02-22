//
// Created by dideldumm on 06.10.24.
//

#include "PolygonalChain.h"
#include <ranges>

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

PolygonalChain::PolygonalChain(const PolygonalChain &chain, const Point &point) {
}


auto PolygonalChain::find_minimal_squared_distance(const Point &a, const PolygonalChain &b) {
}

auto PolygonalChain::find_minimal_squared_distance(const PolygonalChain &a,
                                                     const PolygonalChain &b) {
    if (a.size() == 1 && b.size() == 1) {
        return CGAL::squared_distance(a.getFirstElement(), b.getFirstElement());
    }
    if (a.size() == 1) {
        return find_minimal_squared_distance(a.getFirstElement(), b);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain &a, const PolygonalChain &b) {
    // auto [connectorA, connectorB, distance] = minimalDistance(a, b);
    // addAllElements(connectorA == Last, a.elements);
    // addAllElements(connectorB == First, b.elements);,
}
